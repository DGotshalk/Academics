"""
CS 440 Hidden Markov Model Assignment

Travis Mandel, modified from
an assignment by Sravana Reddy
"""

import string
import math

# The HMM Model
#
# In this HMM, states and observations are represented by strings (usually single characters)
#
# Transitions are stored as a nested map from starting state
#  and ending state to probability. So to get the
# probability of going from state i to state j, one
# should do self.transitions[i][j]
#
# The initial probabilities are stored in the same data structure,
# but the starting state is set to a special value '#'
# So self.transitions['#'][j] representes the probability of being
# in state j initially.
#
# Emissions are stored as a nested map from starting state
#  and emission to probability. So to get the
# probability of getting emission e in state i, one
# should do self.emissions[i][e]
#
# NOTE: Emissions/Transitions that are missing from the maps are assumed to
# have probability 0.
#
# You can get the states with self.states, but be careful as this does not
# include the start state #.
class HMM:

    def __init__(self, transitions=None, emissions=None):
        self.transitions = transitions
        self.emissions = emissions
        if self.emissions:
            self.states = list(self.emissions.keys()) #note: self.states excludes the start state
            

    #Gets the probability of an emission that is not in the emissions dicts
    # might be helpful for your filter and viterbi functions
    def getUnkEmis(self, s):
        if "UNKNOWN" in self.emissions[s]:
            return self.emissions[s]["UNKNOWN"]
        else:
            return 0
        
    # Read HMM from files
    # It reads separate files for the emissions (basename.emit) and for the
    # transitions (basename.trans)
    # Files are read line-by-line, with a separate transition or emission
    # probability on each line
    def load(self, basename):
        
        transf = open(basename+ ".trans", "r")
        self.transitions = {}
        self.emissions = {}
        for line in transf:
            if len(line.strip()) == 0:
                continue
            tokens = line.split(" ")
            fromstate = tokens[0].strip()
            tostate = tokens[1].strip()
            prob = 0
            if len(tokens) > 2:
                prob = float(tokens[2])
            if fromstate not in self.transitions:
                self.transitions[fromstate] = {}
            self.transitions[fromstate][tostate] = prob
        transf.close()
            
        emitf = open(basename+ ".emit", "r")
        for line in emitf:
            if len(line.strip()) == 0:
                continue
            tokens = line.split(" ")
            state = tokens[0].strip()
            obs = tokens[1].strip()
            prob = 0
            if len(tokens) > 2:
                prob = float(tokens[2])
            if state not in self.emissions:
                self.emissions[state] = {}
            self.emissions[state][obs] = prob
        emitf.close()
        self.states = list(self.emissions.keys())
            
        
    # Write HMM to file
    # It writes out two files: one for the emissions (basename.emit) and
    # the other for the transitions (basename.trans)
    # Files are written line-by-line, with a separate transition or emission
    # probability on each line
    def dump(self, basename):
        transf = open(basename+ ".trans", "w+")
        for fromstate in self.transitions:
            for tostate in self.transitions[fromstate]:
                prob = self.transitions[fromstate][tostate]
                if prob is not None and prob > 0:
                    transf.write(fromstate + " " + tostate + " " + str(prob) + "\n")
        transf.close()

        emitf = open(basename+ ".emit", "w+")
        for state in self.emissions:
            for obs in self.emissions[state]:
                prob = self.emissions[state][obs]
                if prob is not None and prob > 0:
                    emitf.write(state + " " + obs + " " + str(prob) + "\n")
        emitf.close()

        
                    

    # Given an observation, runs the forward algorithm
    # This should return the unnormalized forward beliefs,
    # aka alpha_i(t), in the form beliefs[t][i]
    def forward(self, observation):
        obs = observation.asList()
        # YOUR CODE HERE
        
        beliefs = []
        for t in range(len(obs)):
            beliefs.append({})
            prevStates = None
            prevBeliefs = None
            
            for s in self.states:
                beliefs[t][s]=0
                
                if t== 0:
                    #special start state
                    prevStates = ['#']
                    prevBeliefs = {'#':1.0}
                
                else:
                    prevStates=self.states
                    prevBeliefs= beliefs[t-1]

                for prevS in prevStates:
                    prevB = prevBeliefs[prevS]
                    beliefs[t][s] += prevB * self.transitions[prevS][s] #transition (passage of time)
                
                obs_probs = self.emissions[s].get(obs[t], self.getUnkEmis(s))
                beliefs[t][s]*=obs_probs
        
        return beliefs 
    
            


    #Computes the overall probability of the output sequence
    # using the forward algorithm.
    # This function is correct, do not change!
    def forward_probability(self, observation):
        t = len(observation)-1
        res = self.forward(observation)
        if res is None:
            return -1
        return sum(res[t].values())

    #Runs the viterbi algorithm on an observation
    # and returns a list of hidden states
    # indicating the most likely sequence given the model
    def viterbi(self, observation):
        
        obs = observation.asList()
        # YOUR CODE HERE
        
        beliefs= []
        Viterbiargmax=[]
        for t in range(len(obs)):
            Viterbiargmax.append({})
            beliefs.append({})
            prevStates = None
            prevBeliefs = None    
            for s in self.states:
                beliefs[t][s]=0
                if t== 0:
                    #special start state
                    prevStates = ['#']
                    prevBeliefs = {'#':1.0}                
                else:
                    prevStates=self.states
                    prevBeliefs= beliefs[t-1]
                maxb = None
                for prevS in prevStates: 
                    # the important thing about the viterbi is that you take the max of the incoming weights 
                    # multiplied by the probability of where they came from before, instead of summing them, so take the max of prevb* self.transition instead of +=
                    prevB = prevBeliefs[prevS]
                    incomingweights = prevB * self.transitions[prevS][s]
                    if maxb is None or incomingweights > maxb: #we only want a single maximum weight from all the previous states 
                        maxb = incomingweights
                        argmax = prevS
                beliefs[t][s] = maxb #transition (passage of time)
                Viterbiargmax[t][s] = argmax
                obs_probs = self.emissions[s].get(obs[t], self.getUnkEmis(s))
                beliefs[t][s]*=obs_probs
            
        Statesequence = []
        finaltime = len(obs) -1
        Fmax = None
        # this for loop finds the last maximum
        for s in self.states:
           val = beliefs[finaltime][s]
           if Fmax is None or val > Fmax:
               Fmax = val
               finalstate = s
        Statesequence.insert(0,finalstate)
        
        for t in range(len(obs)-1,0,-1):# from the second to last to the first, put the argmax of the state into our list, and then travel to that state
            argmax = Viterbiargmax[t][finalstate]
            Statesequence.insert(0,argmax)
            finalstate = argmax 
        return Statesequence


    # Given a corpus, consisting of observations labeled with known
    # states, learns the parameters of the HMM in an unsupervised fashion.
    #  Should use Lapace-style smoothing with a parameter of 0.01
    def learn_supervised(self, corpus):
        #Here's a starting point to iterate through the
        #transitions = {}
        #transitions["#"] = {}
        #emissions = {}
        epsilon = 0.01
        

        for obs in corpus:
            obsList = obs.asList()
            stateList = obs.getKnownState()
            if stateList[0] in self.transitions["#"]:
                self.transitions["#"][stateList[0]] += 1.0
            else:
                self.transitions["#"][stateList[0]] =1.0
            
            for initial, nextstate in zip(stateList, stateList[1:]):
                if initial in self.transitions: 
                    if nextstate in self.transitions[initial]:
                        self.transitions[initial][nextstate] += 1.0
                    else:
                        self.transitions[initial][nextstate] = 1.0
                else:
                    self.transitions[initial] = {nextstate:1.0}

 
            for state,observ in zip(stateList, obsList):
                if state in self.emissions:
                    if observ in self.emissions[state]:
                        self.emissions[state][observ] +=1.0
                    else:
                        self.emissions[state][observ] = 1.0
                else:
                    self.emissions[state] = {observ: 1.0} 
        
            #transitions should now hold the number of starting transitions
            # YOUR CODE HERE

        emissionprob = {}
        # we now want to compile the probability of a emission given some state x
        statecounts = {}
        
        for state in self.emissions:
            # getting total number of times initial state had an emission 
            numseen = 0
            
            if state not in statecounts:
                for emis in self.emissions[state]:
                    numseen += self.emissions[state][emis]
                statecounts[state] = numseen
            
            emissionprob[state] = {} 
            for observ in self.emissions[state]:
                #calculating the probabilities of an observation given its initial state 
                
                numerator = self.emissions[state].get(observ, self.getUnkEmis(state)) + epsilon
                
                denominator = statecounts[state] + epsilon*(len(self.emissions[state])+1)
                
                prob = numerator/denominator
                self.emissions[state][observ]  = prob
           
        #self.emissions = emissionprob
         
        transitionprobabilities ={}

        initialstatecount = {}


        for initial in self.transitions:
            #getting total number of times initial state was an intital state 
            numseen = 0
            if initial not in initialstatecount:
                for nexts in self.transitions[initial]:
                    numseen += self.transitions[initial][nexts]
                initialstatecount[initial] = numseen
            transitionprobabilities[initial] = {} 
            for nextstate in self.transitions[initial]:          
                numerator = self.transitions[initial][nextstate] + epsilon
                denominator = initialstatecount[initial] + epsilon*(len(self.transitions[initial]))
                prob = numerator/denominator
                
                transitionprobabilities[initial][nextstate] = prob
        self.transitions = transitionprobabilities

    


        #pass #remove once implemented
            

    # Given an observation, runs the backward algorithm
    # This should return the unnormalized backwards beliefs,
    # aka beta_i(t), in the form beliefs[t][i]
    def backward(self, observation):
        obs = observation.asList()
        # YOUR CODE HERE
        
        beliefs = []
        backwardbelief = []
        for _ in range(len(obs)):
            beliefs.append({})
            backwardbelief.append({}) 
        for t in range(len(obs)-1,-1,-1):
            prevStates = None
            prevBeliefs =None
            for s in self.states:
                beliefs[t][s] = 0

                if t == len(obs)-1:
                    prevStates = ['#']
                    prevBeliefs = {'#':1.0}
                    beliefs[t][s] = 1
                    backwardbelief[t][s] = self.emissions[s].get(obs[t],self.getUnkEmis(s))
                    continue
                
                else:
                    prevStates = self.states
                    prevBeliefs = backwardbelief[t+1]
                
                for prevS in prevStates:
                    prevB = prevBeliefs[prevS]
                    beliefs[t][s] += prevB * self.transitions[s][prevS]
                backwardbelief[t][s] = beliefs[t][s] *self.emissions[s].get(obs[t],self.getUnkEmis(s))

        return beliefs 
        

    #Computes the overall probability of the output sequence
    # using the backward algorithm.
    # This function is correct, do not change!
    def backward_probability(self, observation):

        #Got to push backwards prob on time 0 back to initial state
        res = self.backward(observation)
        if res is None:
            return -1
        obs = observation.asList()
        finalRes = 0
        for s in res[0]:
            finalRes += res[0][s]* \
                self.transitions['#'][s]*self.emissions[s].get(obs[0],0)
        return finalRes
    
    # Runs the EM aka Baum Welch aka Forward-Backward algorithm
    # to learn the parameters of the HMM without any supervision.
    #
    # The data comes in a corpus, where each element of the corpus
    # is a sequence of type Observation.  Consider doing observation.asList()
    # to make these sequences easier to work with.
    #
    # The algorithm should stop when the log-likelihood changes by less than
    # 'convergence'.  It's probabaly a good idea to print out the log-likelihood
    # on each iteration so you can see what is going on.
    #
    # Should return the final log-likelihood of the entire corpus.
    #
    # Note: DO NOT initialize the parameters randomly, they should already be
    #    initialized to something when this method is called.
    def learn_unsupervised(self, corpus, convergence=0.069):
        
        
        pass #remove once implemented
       
    
    #Is this HMM equal to another HMM, with some tolerance?
    def isEqual(self, other, tolerance):
        for i in self.transitions:
            if i not in other.transitions:
                print("Extra transition: " + str(i)) 
                return False
            for j in self.transitions[i]:
                if abs(self.transitions[i][j] - other.transitions[i].get(j,0)) > tolerance:
                    print("Transitions differ! " +i +" " + j +" "+ str(self.transitions[i][j]) + " " +str( other.transitions[i].get(j,0)))
                    return False
        for j in other.transitions:
            if j not in self.transitions:
                print("Missing transition: " + str(j)) 
                return False
        for i in self.emissions:
            if i not in other.emissions:
                print("Extra emission: " + str(i)) 
                return False
            for e in self.emissions[i]:
                if abs(self.emissions[i][e] - other.emissions[i].get(e,0)) > tolerance:
                    print("Emissions differ! " +i +" " + e +" "+ str(self.emissions[i][e]) + " " +str( other.emissions[i].get(e,0)))
                    return False
        for j in other.emissions:
            if j not in self.emissions:
                print("Missing emission: " + str(j)) 
                return False

        return True
        


    def plusEquals(self, dic, key, value):
        oldval = dic.get(key, 0)
        dic[key] = oldval + value

    
        
                
            

 
