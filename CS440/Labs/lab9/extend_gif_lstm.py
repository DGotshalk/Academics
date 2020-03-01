#CS440 Lab 9: LSTM GIFs
# (C) 2019 Travis Mandel
import zipfile

from __future__ import print_function
import keras
from keras.callbacks import LambdaCallback
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import Reshape
from keras.layers import Flatten
from keras.layers import LSTM
from keras.layers.convolutional import Conv3D
from keras.layers.convolutional import Conv2D
from keras.layers.convolutional_recurrent import ConvLSTM2D
from keras.layers.normalization import BatchNormalization
from keras.optimizers import RMSprop
from keras.utils.data_utils import get_file
import numpy as np
import random
import sys
import io
import os
from PIL import Image
from io import BytesIO





# This is the maximum length of the sequence we pass to the LSTM.
# It's this short to keep things faster/simpler.
maxLength = 8
#This will contain lists of input sequences to feed to the LSTM.
xList = []
yList = []

#Remember the first few frames of red, green, and blue for each
# gif.  This is used later when we want to test how the LSTM
# extends the GIFs.
rList = []
gList = []
bList = []


#images are very small at 32x32, as indicated by this constant.
# This is mostly for speed reasons.
imSize = 32


#Colaboratory doesn't make it easy to upload lots of tiny
# little files.  So I had to make the script reading the
# traing images directly out of a zip file
with zipfile.ZipFile("train_small.zip", "r") as f:
    for fname in f.namelist():
        data = f.read(fname)
        f2 = BytesIO(data)
        im = Image.open(f2)
        l,w = im.size
        if l != 32 or w != 32:
            #Bad file, skip it
            continue
        frameNum =0
        curXList = []
        
        curRList = []
        curGList = []
        curBList = []
        addedRGB = False

        # For each video, consider only the R, g , or B channel.
        # To simplify/speed training, we train one network,
        # then use it separately on the R, G, and B channels.
        channel = random.randrange(3)
        try:
            while True: #Want to say "while there are more frames in GIF" but Pillow makes this hard
                imf = Image.new('RGBA', im.size)
                imf.paste(im, (0, 0), im.convert('RGBA'))
                imf = imf.resize((imSize,imSize))
                
                imnp = np.array(imf.convert("RGB"))
                (l,w,c) = imnp.shape

                #For some reason the LSTM layer needs a 3d input
                # so make it 32x32x1
                curRList.append(list(np.reshape(imnp[:,:, 0], (imSize,imSize,1))))
                curGList.append(list(np.reshape(imnp[:,:, 1], (imSize,imSize,1))))
                curBList.append(list(np.reshape(imnp[:,:, 2], (imSize,imSize,1))))
                                
                                
                tempX = np.reshape(imnp[:,:, channel], (imSize,imSize,1))
                curXList.append(tempX)
                frameNum += 1
                
                #only add the begiining of each GIF to the RGB list
                if len(curXList) == maxLength+1 and not addedRGB: 
                        rList.append(curRList[:-1])
                        gList.append(curGList[:-1])
                        bList.append(curBList[:-1])
                        addedRGB = True
                #This is needed  to move to the next frame (if there is one)
                im.seek(im.tell() + 1)
        except EOFError:
            pass # Finished with the file, just need to exit the loop!
        curXList = np.array(curXList)
        for i in range(len(curXList) - maxLength -1):
            xList.append(curXList[i:i+maxLength])
            yList.append(curXList[i+maxLength] /255.0)  #Very imporant here to scale the output between 0 and 1

    

    


# This is where the model is built
print('Building model...')
seq = Sequential()

#This does the bulk of the work, its an Convolutional LSTM
# layer that runs through the sequence.  Returns only the final output.
seq.add(ConvLSTM2D(filters=15, kernel_size=(3, 3),
                   input_shape=(None, imSize, imSize,1),
                   padding='same', return_sequences=False))

#This final convolutional layer helps to "fine-tune" the output.
# Note that the output is sigmoid, which is fine since each output pixel is betwen 0 and 1
seq.add(Conv2D(filters=1, kernel_size=(3, 3),
               activation='sigmoid',
               padding='same', data_format='channels_last'))
seq.compile(loss='mean_squared_error', optimizer='adadelta') # binary_crossentropy and mean_squared_error

model = seq
model.summary()


mygif = None

# Function invoked at end of each epoch. Writes out a gif that starts with the first
# few frames as original, then queries the LSTM for output from the next frames
mygif = None
def on_epoch_end(epoch, _):
    
    print()
    print('----- Saving gif after Epoch: ', (epoch+1))
    if mygif ==None:
        #Pick a random gif from the training dataset, initialize the frame lists
        startIndex = random.randint(0, len(rList) - 1)
        startR = list(rList[startIndex])
        startG = list(gList[startIndex])
        startB = list(bList[startIndex])
        allFrames = []
    else:
        startR = list(rList[0])
        startG = list(gList[0])
        startB = list(bList[0])
        allFrames = []

    # This part just adds the initial frames of the original gif onto the
    # allFrames list we are building up.
    for i in range(len(startR)):
        arrFrame = np.zeros((imSize,imSize,3))
        arrFrame[:,:,0] = np.reshape(startR[i], (imSize,imSize))
        arrFrame[:,:,1] = np.reshape(startG[i], (imSize,imSize))
        arrFrame[:,:,2] = np.reshape(startB[i], (imSize,imSize))
        imToShow = Image.fromarray(arrFrame.astype('uint8'), 'RGB')
        imToShow = imToShow.resize((256,256), Image.NEAREST) #Resize to 256xz256 to make it easier to see!
        allFrames.append(imToShow)

    #Add 30 new frames predicted by the LSTM
    for i in range(30):
            #Convert history lists to numpy arrays
            rHist = np.array([startR])
            gHist = np.array([startG])
            bHist = np.array([startB])

            #Use the model to predict the next frame.
            # Remember it's in [0,1] so we need to rescale.
            rPreds = np.reshape(model.predict(rHist, verbose=0)[0]*255.0, (imSize,imSize,1))
            gPreds = np.reshape(model.predict(gHist, verbose=0)[0]*255.0, (imSize,imSize,1))
            bPreds = np.reshape(model.predict(bHist, verbose=0)[0]*255.0, (imSize,imSize,1))

            arrFrame = np.zeros((imSize,imSize,3))
            # Just in case something went out of bounds
            nextR = np.clip(rPreds , 0, 255)
            nextB = np.clip(gPreds, 0, 255)
            nextG = np.clip(bPreds, 0, 255)
            # Pack the info into the new frame
            arrFrame[:,:,0] = np.reshape(nextR, (imSize,imSize))
            arrFrame[:,:,1] = np.reshape(nextG, (imSize,imSize))
            arrFrame[:,:,2] = np.reshape(nextB, (imSize,imSize))
            imToShow = Image.fromarray(arrFrame.astype('uint8'), 'RGB')
            imToShow = imToShow.resize((256,256), Image.NEAREST) #Agin, resize to make it easier to see
            allFrames.append(imToShow)
            
            startR.pop(0)
            startG.pop(0)
            startB.pop(0)
            startR.append(nextR)
            startG.append(nextG)
            startB.append(nextB)
            #TODO: Add some lines here to update the history and stop the GIF from freezing


    #Compile and save the final GIF
    if mygif == None:
        allFrames[0].save("epoch" + str(epoch) + ".gif", 'GIF', optimize=True, save_all=True, append_images=allFrames[1:], duration=50, loop=1000)
    else:
        allFrames[0].save("TrainedDoge"+ ".gif", 'GIF', optimize=True, save_all=True, append_images=allFrames[1:], duration=50, loop=1000)
#Cause our function to be called after each ecpoch
print_callback = LambdaCallback(on_epoch_end=on_epoch_end)

x = np.array(xList)
y = np.array(yList)
#Run the training for 5 epochs.
model.fit(x, y,
          batch_size=128,
          epochs=5,
          callbacks=[print_callback])



mygif = 1

xList = []
yList = []
rList = []
gList = []
bList = []
imSize = 32


im = Image.open("RaveDoge.gif")
l,w = im.size
if l != 32 or w != 32:
    print(l,w)
    print("badfile")
frameNum =0
curXList = []  
curRList = []
curGList = []
curBList = []
addedRGB = False
# For each video, consider only the R, g , or B channel.
# To simplify/speed training, we train one network,
# then use it separately on the R, G, and B channels.
channel = random.randrange(3)
try:
    while True: #Want to say "while there are more frames in GIF" but Pillow makes this hard
        imf = Image.new('RGBA', im.size)
        imf.paste(im, (0, 0), im.convert('RGBA'))
        imf = imf.resize((imSize,imSize))
        
        imnp = np.array(imf.convert("RGB"))
        (l,w,c) = imnp.shape

        #For some reason the LSTM layer needs a 3d input
        # so make it 32x32x1
        curRList.append(list(np.reshape(imnp[:,:, 0], (imSize,imSize,1))))
        curGList.append(list(np.reshape(imnp[:,:, 1], (imSize,imSize,1))))
        curBList.append(list(np.reshape(imnp[:,:, 2], (imSize,imSize,1))))
                        
        tempX = np.reshape(imnp[:,:, channel], (imSize,imSize,1))
        curXList.append(tempX)
        frameNum += 1
        
        #only add the begiining of each GIF to the RGB list
        if len(curXList) == maxLength+1 and not addedRGB: 
                rList.append(curRList[:-1])
                gList.append(curGList[:-1])
                bList.append(curBList[:-1])
                addedRGB = True
        #This is needed  to move to the next frame (if there is one)
        im.seek(im.tell() + 1)
except EOFError:
    pass # Finished with the file, just need to exit the loop!
curXList = np.array(curXList)
for i in range(len(curXList) - maxLength -1):
    xList.append(curXList[i:i+maxLength])
    yList.append(curXList[i+maxLength] /255.0)  #Very imporant here to scale the output between 0 and 1

print_callback = LambdaCallback(on_epoch_end=on_epoch_end)

x = np.array(xList)
y = np.array(yList)
#Run the training for 5 epochs.
model.fit(x, y,
          batch_size=128,
          epochs=1,
          callbacks=[print_callback])