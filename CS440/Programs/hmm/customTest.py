import hmm
import observations
import codecs

model = hmm.HMM()
model.load("models/partofspeech.student.trained")
obsfilebase = "data/custom_sents"
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
