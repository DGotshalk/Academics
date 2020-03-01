# CS 440 Multi-Armed Bandit Assignment
# (C) 2017 Travis Mandel

#These imports should be sufficient
import random
from  math import sqrt, log
import environments as envs
import distributions as dists

# Interface (abstract) for multiarmed bandit learners
# Don't change this
class MABLearner(object):

    # Re-initializes the MAB with a given MABEnvironment
    # Returns True if initialization was successful, False otherwise
    def initWithEnvironment(self,env):
        pass

    #Chooses an arm to pull based on all the rewards processed so far
    # Arms are represented as integers, so it just needs to return a
    # number between 0 and the number of arms in the environment
    def chooseArm(self):
        pass

    #Processes a reward
    def processReward(self, arm, reward):
        pass


# Implements the epsilon-greedy algorithm as discussed in class
class EpsilonGreedy(MABLearner):

    def __init__(self, epsilon):
        self.epsilon = epsilon

    def initWithEnvironment(self,env):
        self.env = env
        self.armTotals = []
        self.armCounts = []
        for arm in range(self.env.getNumArms()):
            self.armTotals.append(0)
            self.armCounts.append(0)
        return True #Change to return True once implemented

    def chooseArm(self):
        #pick random number for our baby epsolon 
        if random.random() < self.epsilon:
            return random.randrange(self.env.getNumArms())
        maxArm = None
        maxReward = None
        for arm in range(self.env.getNumArms()):
            if self.armCounts[arm] ==0:
                continue
            meanR = self.armTotals[arm]/self.armCounts[arm]
            if maxReward is None or meanR > maxReward:
                maxArm = arm
                maxReward = meanR
        if maxArm is None:
            return random.randrange(self.env.getNumArms())
        return maxArm 
    
    def processReward(self,arm, reward):
        self.armTotals[arm] += reward
        self.armCounts[arm] += 1

# Implements the UCB algorithm as discussed in class
class UCB(MABLearner):

    def __init__(self, alpha):
        self.alpha = alpha
    
    def initWithEnvironment(self,env):
        self.env = env
        self.times = 0 # i say times, really should be num rewards 
        self.armTotals = []
        self.armCounts = []
        for arm in range(self.env.getNumArms()):
            self.armTotals.append(0)
            self.armCounts.append(0)
        return True #Change to return True once implemented
         
    def chooseArm(self):
        for arm in range(self.env.getNumArms()):
            if self.armCounts[arm] == 0:  
                return arm
                 
        maxArm = None
        maxReward = None 
        for arm in range(self.env.getNumArms()):
            
            meanR = self.armTotals[arm]/self.armCounts[arm]
            
            reward = meanR + self.alpha*sqrt(2*log(self.times)/self.armCounts[arm])
            if maxReward is None or reward > maxReward:
                maxArm = arm
                maxReward = reward
        
        return maxArm
        
    def processReward(self, arm, reward):
        # env.getmin get env.getmax to scale 
        reward = (reward - self.env.getMinReward())/(self.env.getMaxReward() - self.env.getMinReward())
        """
        if reward < 0:
            reward = 0
        if reward > 1:
            reward = reward/100
        """
        self.armTotals[arm] += reward
        self.armCounts[arm] += 1
        self.times+=1 

# Implements the Beta-Bernoulli thompson sampling algorithm as discussed
#in class.
#Should handle the straightforward extension to non-discrete variables.
class ThompsonDiscrete(MABLearner):

    def __init__(self):
        pass 
    def initWithEnvironment(self,env):
        self.armDistribution = []
        self.armCounts = []
        self.env = env
        for arm in range(self.env.getNumArms()):
            self.armDistribution.append(dists.BetaDistribution(1,1))
            self.armCounts.append(0)
        return True

    def chooseArm(self):
        maxArm = None
        maxReward = None
        for arm in range(self.env.getNumArms()):
            reward = self.armDistribution[arm].sample()
            if maxReward is None or reward > maxReward:
                maxReward = reward
                maxArm = arm
        return maxArm
        
        
    def processReward(self,arm, reward):
        """
        if reward < 0:
            reward = 0
        if reward > 1:
            reward = reward/100
        """
        
        reward = (reward - self.env.getMinReward())/(self.env.getMaxReward() - self.env.getMinReward())

        if reward != 0 and reward != 1:
            if random.random() < reward:
                reward = 1 
            else:
                reward = 0      
            
        if reward == 0: 
            self.armDistribution[arm].beta += 1
        elif reward == 1:
            self.armDistribution[arm].alpha += 1
        




        

