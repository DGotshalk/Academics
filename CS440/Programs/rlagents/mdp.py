# CS 440 Reinforcement Learning Assignment
# (C) 2017 Travis Mandel

import random
import distributions as dists
import sys

#Interface provided to the learner for getting the known aspects of the environment
#Takes in a fully defined environment and "hides" unknown info
class MDP:
    #obsProbs must be a map from (s,a) --> list of outcome probabilities
    def  __init__(self, env, obsProbs):
        self.env = env
        self.obsProbs = obsProbs
        if not self.validate():
            sys.exit(-1)
		
    def validate(self):
        for pair in self.obsProbs:
            probs = self.obsProbs[pair]
            if abs(1-sum(probs)) > 0.0001:
                print("Trying to construct invalid mdp! (s,a)= " + \
                      str(pair) + " oProbs " + str(probs))
                return False
            
        return True
    
    def Q(self, state,action, o, timestep):
        # check getnextstaee is a value
        if self.env.getNextState(state,action,o) is None:
            return self.obsProbs[(state, action)][o]*(self.env.getReward(state, action, o) + 0)
        else:
            return self.obsProbs[(state, action)][o]*(self.env.getReward(state, action, o) + self.computeV(self.env.getNextState(state, action, o),timestep+1))

    def computeV(self, state, timestep):
        
        if timestep == self.env.getTimeHorizon():
            self.Val[(state,timestep)] = 0 
            return self.Val[(state, timestep)]
        
        if (state, timestep) in self.Val:
            return self.Val[(state,timestep)] 
        
        else:
            maxval = None
            maxact = None
            for action in range(self.env.getNumActions()):
                if self.env.isActionValid(state, action) is True: # for all valid actions from out state
                    val = None
                    for o in range(self.env.getNumOutcomes()): # sum over the outcomes
                        if val is None:
                            val = self.Q(state,action,o, timestep)                        
                        else: 
                            val+= self.Q(state,action,o, timestep)
           
                    if maxval is None or maxval < val: # find the maximum value and save the argmax as well
                        maxval = val
                        maxact = action 
            self.Val[(state,timestep)] = maxval
            self.policy[(state,timestep)] = maxact
            return self.Val[(state,timestep)]
    
    # Should return a dict mapping (s,t) --> a
    # Where a is the optimal long-term action to take in this MDP
    def computeOptimalPolicy(self):
        self.policy = {}
        self.Val = {}
        self.computeV(self.env.getInitialState(), 0) 
        return self.policy


    def sampleOutcome(self, state, action):
        if not self.env.isActionValid(state, action):
            print("Error: Trying to take invalid action. " + \
                  "At state " + str(state) + " taking action " + str(action))
            sys.exit(-1)
        probs = self.obsProbs[(state,action)]
        choice = random.random()
        sumP = 0
        for i in range(len(probs)):
            sumP += probs[i]
            if choice < sumP:
                return i

        print("Error! Should have sampled a value by now!")
        sys.exit(-1)
            
                    
                
