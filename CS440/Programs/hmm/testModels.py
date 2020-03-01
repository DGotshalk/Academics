"""
CS 440 Hidden Markov Model Assignment

Travis Mandel, modified from
an assignment by Sravana Reddy
"""

import random
import argparse
import codecs
import os
import sys
import hmm
import observations



def compareFiles(student, ref, ignoreOrder=False):
    sfile = open(student, "r")
    rfile = open(ref, "r")
    if ignoreOrder:
        slines = set()
        rlines = set()
        for sline in sfile:
            slines.add (sline)
            
        for rline in rfile:
            rlines.add(rline)
        if len(slines) != len(rlines):
            print("Different number of lines! student has " + str(len(slines))\
                    + " but ref has " + str(len(rlines)))
            return False
        for sline in slines:
            if sline not in rlines:
                print("Incorrect student line: " + str(sline))
                return False
        sfile.close()
        rfile.close()
        return True
            
    slines = []
    rlines = []
    for sline in sfile:
        slines.append (sline)
        
    for rline in rfile:
        rlines.append(rline)
    if len(slines) != len(rlines):
        print("Different number of lines! student has " + str(len(slines))\
                + " but ref has " + str(len(rlines)))
        return False
    for i in range(len(slines)):
        try:
            sVal = float(slines[i])
            rVal = float(rlines[i])
            if abs(sVal - rVal) > 1e-10:
                print("Incorrect student value: " + str(slines[i]) + " should be " + str(rlines[i]))
                return False
        except ValueError:
            if slines[i] != rlines[i]:
                print("Incorrect student line: " + str(slines[i]) + " should be " + str(rlines[i]))
                return False
    sfile.close()
    rfile.close()
    return True

# main
def main():

    model = hmm.HMM()



    print("-------------Preliminary setup----------------")
    if True:
        existingFile = 'models/two_english'
        newFile = "two_english_test"
        model.load(existingFile)
        model.dump(newFile)
        eq = compareFiles(newFile + ".emit", existingFile+".emit", True)
        if eq:
            eq2 = compareFiles(newFile + ".trans", existingFile+".trans", True)
        if eq and eq2:
            print("HMM read/write works correctly")
        else:
            print("HMM read/write failed!")
            sys.exit(-1)
   
            
    print("-------------Forward Algorithm----------------")
    if True:
        model.load("models/encoding.message.trained")
        obsfilebase = "data/message_short"
        corpus = observations.load_observations(obsfilebase+".obs")
        outputfile = obsfilebase+'.forwardprob'
        o2 = []
        with open(outputfile, 'w') as o:
            for observation in corpus:
                res = model.forward(observation)
                if res is not None:
                    o2.append(res[1]['e'])
                o.write(str(model.forward_probability(observation))+'\n')
        #print(o2)
        refo2 = [2.281674056874541e-61, 8.258943021002516e-289, 4.463852239881595e-71, 7.902572774713472e-90, 2.8349675683293275e-292, 0.00021461328799181662, 2.8704406377717645e-145, 5.979495606734988e-294, 1.9000669411442752e-05, 2.02982042347432e-87, 2.116898876762055e-70, 0.0, 0.002086363130808398, 3.156654312658676e-293]
        for i in range(len(refo2)):
            if len(o2) <= i:
                print("Error: Nothing returned from Forward Algorithm!")
            elif abs(o2[i] -refo2[i]) > 1e-12:
                print("Error in Forward Algorithm: Probability of e at t=1 should be " + str(refo2[i]) + " not " + str(o2[i]))


        eq = compareFiles(outputfile, "gold/message_short.forwardprob")
        if eq:
            print("Forward Algorithm passed basic sanity check")
        else:
            print("Error in Overall Forward Probability")

    print("-------------Supervised Learning----------------")
    if True:
        modelbase = "models/partofspeech"
        model.load(modelbase)
        obsfilebase = "data/browntags"
        corpus = observations.load_observations(obsfilebase+".obs")
        model.learn_supervised(corpus)
        finalprefix = modelbase+'.student.trained'
        model.dump(finalprefix)
        goldprefix = "gold/partofspeech.browntags.trained"


        learnedModel = hmm.HMM()
        learnedModel.load(finalprefix)

        refModel = hmm.HMM()
        refModel.load(goldprefix)
        
        eq = learnedModel.isEqual(refModel, 1e-8)
        if eq:
            print("Supervised learning implemented correctly!")
        else:
            print("Error in supervisedlearning")
            
    print("-------------Viterbi Algorithm----------------")
    if True:
        model.load("models/encoding.message.trained")
        obsfilebase = "data/message"
        corpus = observations.load_observations(obsfilebase+".obs")
        outputfile = obsfilebase+'.tagged.obs'

        with codecs.open(outputfile, 'w', 'utf8') as o:
            for observation in corpus:
                stateseq = model.viterbi(observation)
                if stateseq is None:
                    continue
                observation.stateseq = stateseq  # adds most likely states as
                                                 # 'tags' on observation
                o.write(str(observation))

        eq = compareFiles(outputfile, "gold/message.tagged.obs")
        if eq:
            print("Viterbi Completed Successfully")
        else:
            print("Error in Viterbi")
        


    print("-------------Backwards Algorithm----------------")
    if True:
        model.load("models/encoding.message.trained")
        obsfilebase = "data/message_short"
        corpus = observations.load_observations(obsfilebase+".obs")
        outputfile = obsfilebase+'.backwardprob'
        o2 = []
        with open(outputfile, 'w') as o:
            for observation in corpus:
                res = model.backward(observation)
                if res is not None:
                    o2.append(res[1]['e'])
                o.write(str(model.backward_probability(observation))+'\n')
        refo2 = [1.316154528121009e-06, 1.0, 1.0, 1.2842129295716715e-05, 1.0, 1.0, 0.0001629601877945561, 0.03761379913095424, 2.464196513136796e-06, 4.079841777243271e-12, 1.0, 4.2966181326644535e-08, 1.0, 1.0]
        for i in range(len(refo2)): 
            if len(o2) <= i:
                print("Error: Nothing returned from Backward Algorithm!")
            elif abs(o2[i] -refo2[i]) > 1e-10:
                print("Error in Backward Algorithm: Probability of e at t=1 should be " + str(refo2[i]) + " not " + str(o2[i]))

        eq = compareFiles(outputfile, "gold/message_short.backwardprob")
        if eq:
            print("Backward Algorithm passed basic sanity check")
        else:
            print("Error in Overall Backward Probability")

    print("------------------EM--------------------")
    if True:
        modelbase = "models/two_english"
        model.load(modelbase)
        obsfilename = "english_words"
        obsfilebase = "data/" + obsfilename
        corpus = observations.load_observations(obsfilebase+".obs")
        log_likelihood = model.learn_unsupervised(corpus)
        #write the trained model
        ref_likelihood =  -105954.94191 # -152860.669251 in base 2
        if log_likelihood is None or abs(log_likelihood - ref_likelihood) > 0.05:
            print("Error: likelihood should be " + str(ref_likelihood) + \
                  " but is " + str(log_likelihood))
        finalprefix = modelbase+'.'+obsfilename+'.trained'
        model.dump(finalprefix)
        goldprefix = "gold/two_english.english_words.trained"


        learnedModel = hmm.HMM()
        learnedModel.load(finalprefix)

        refModel = hmm.HMM()
        refModel.load(goldprefix)
        
        eq = learnedModel.isEqual(refModel, 1e-10)
        if eq:
            print("EM implemented correctly!")
        else:
            print("Error in EM")

if __name__=='__main__':
    main()
