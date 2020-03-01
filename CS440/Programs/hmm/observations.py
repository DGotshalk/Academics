"""
CS 440 Hidden Markov Model Assignment

Travis Mandel, modified from
an assignment by Sravana Reddy
"""

import random
import argparse
import codecs
import os

# observations
# Kind of weird in that it optionally takes in
# parallel states as "tags" on the original observations
class Observation:
    def __init__(self, stateseq, outputseq):
        self.stateseq = stateseq
        self.outputseq = outputseq  # sequence of outputs
    def __str__(self):
        return ' '.join(self.stateseq)+'\n' + ' '.join(self.outputseq)+'\n'
    def __repr__(self):
        return self.__str__()
    def __len__(self):
        return len(self.outputseq)

    #This will be helpful for learn_supervised()
    def getKnownState(self):
        #print(self.stateseq)
        return self.stateseq
    
    #Mostly you just need to use this.
    def asList(self):
        return self.outputseq

#Observation helper function
def load_observations(filename):
    lines = [line.split() for line in codecs.open(filename, 'r', 'utf8').readlines()]
    for l in lines:
        for i in range(len(l)):
            l[i] = l[i].strip()
            
    if len(lines)%2==1:  # remove extra lines
        lines[:len(lines)-1]
    return [Observation(lines[i], lines[i+1]) for i in range(0, len(lines), 2)]
