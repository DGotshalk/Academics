# CS 440 Multi-Armed Bandit Assignment
# (C) 2017 Travis Mandel

#These imports should be sufficient
import random
import math
import distributions as dists
import environments as envs

#Write a comment explaining why UCB-1 must always be better than UCB-0.01, or
# a comment explaining your counterexample environment
"""
I think that the reason UCB-0.01 works much better is that when we shrink the confidence intervals, we no longer start pulling worse performing arms until they their confidence intervals finally shrink to the point where we start pulling better arms like we do in UCB-1. with UCB-.01, we are less optimistic about the upper bounds on the arms, so we focus more on the mean instead.


"""

class StudentEnv(envs.MABEnvironment):
    def __init__(self):
        #YOUR CODE HERE
        pass #remove once implemented

    def pull(self,arm):
        #YOUR CODE HERE
        pass #remove once implemented

    def reset(self):
        #YOUR CODE HERE
        return False #Change to return True once implemented
    
    def getNumArms(self):
        #YOUR CODE HERE
        pass #remove once implemented
 
    def getMinReward(self):
        #YOUR CODE HERE
        pass #remove once implemented
		
    def getMaxReward(self):
        #YOUR CODE HERE
        pass #remove once implemented
