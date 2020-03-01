# CS 440 Reinforcement Learning Assignment
# (C) 2017 Travis Mandel

#These imports should be sufficient
import random
import math
import environments as envs
import distributions as dists
import mdp

# Interface (abstract) for reinforcement learning agents
# Don't change this
class RLAgent(object):

    # Re-initializes the agent with a given RLEnvironment
    # Returns True if initialization was successful, False otherwise
    def initWithEnvironment(self,env):
        pass

    #Chooses a a valid action based on all the feedback processed so far
    # Actions are represented as integers, so it just needs to return a
    # number between 0 and the number of actions in the environment
    def chooseAction(self, state, t):
        pass

    #Processes an episode, which is a list of (state, action, outcome) tuples.
    def processEpisode(self, episode):
        pass
	
    #Signals to the agent that a new episode is starting up 
    def episodeStart(self):
        pass


#Implements the Simple Greedy Learner as indicated by the instructions
class SimpleGreedyLearner(RLAgent):

    def __init__(self):
       pass

    def initWithEnvironment(self,env):
        
        self.env = env
        self.rewards = {} # map (s,a) --> (total, count) of rewards
        for state in self.env.getAllStates():
            for action in range(self.env.getNumActions()):
                if not self.env.isActionValid(state,action):
                    continue
                total = 0
                count = 0
                self.rewards[(state,action)] = (total,count)
        return True

    def chooseAction(self, state, t):
        maxActions = None
        maxValue = None
        for a in range(self.env.getNumActions()):
            if not self.env.isActionValid(state,a):
                continue
            (total,count) = self.rewards[(state,a)]
            if count ==0:
                return a
            avg = total/count
            if maxValue is None or avg > maxValue:
                maxValue = avg
                maxActions = [a]
            elif avg == maxValue:
                maxActions.append(a)
        return random.choice(maxActions)
        
    def processEpisode(self, episode):
        for t in range(len(episode)):
            (s, a, o) = episode[t]
            (total, count) = self.rewards[(s,a)]
            reward = self.env.getReward(s,a,o)
            total += reward
            count += 1
            self.rewards[(s,a)] = (total,count)
    
    def episodeStart(self):
        pass # is this right?
		
# Implements the PSRL Algorithm as discussed in class
# Implement the version with alpha_i=1 (uniform)

class PSRL(RLAgent):
    def __init__(self):
        #YOUR CODE HERE
        pass #remove once implemented
        
    def initWithEnvironment(self,env):
        
        self.env = env
        alphas =[]
        for i in range(self.env.getNumOutcomes()):
            alphas.append(1)
        self.distribute = {}  # should map (s,a) - > list of dirichlet 
        self.samples = {}
        for state in self.env.getAllStates():
            for action in range(self.env.getNumActions()): 
                self.distribute[(state,action)] = dists.DirichletDistribution(list(alphas)) 
        return True
         
    def chooseAction(self, state, t):
        return self.policy[(state,t)]
        
    def processEpisode(self, episode):
        for t in range(len(episode)):
            (s,a,o)=episode[t]
            alphas = self.distribute[(s,a)].getAlphas()
            alphas[o] += 1 
            self.distribute[(s,a)] = dists.DirichletDistribution(alphas)
            #self.samples[(s,a)] = self.distribute[(s,a)].sample()

    def episodeStart(self):  
        for state in self.env.getAllStates():
            for action in range(self.env.getNumActions()):  
                self.samples[(state,action)] = self.distribute[(state,action)].sample()
        self.mymdp = mdp.MDP(self.env, self.samples)
        self.policy = self.mymdp.computeOptimalPolicy()


# Implements the finite horizon Q-Learning algorithm as discussed in class
class QLearner(RLAgent):
    def __init__(self, epsilon, alpha):
        self.epsilon = epsilon
        self.alpha = alpha
        
    def initWithEnvironment(self,env): 
        self.env = env
        self.Qvalues = {} # map (s,a,t) --> val #MEMOIZATION
        for state in self.env.getAllStates():
            for action in range(self.env.getNumActions()):
                for t in range(self.env.getTimeHorizon()):
                    self.Qvalues[(state, action, t)] = 0               
        return True
        
    def chooseAction(self, state, t):         
        if random.random() < self.epsilon:
            while True:
                action = random.randrange(self.env.getNumActions())
                if self.env.isActionValid(state, action) is True:
                    return action
        else:
            maxQ = None
            maxact = None
            for action in range(self.env.getNumActions()):
                if self.env.isActionValid(state,action) is True:
                    Q = self.Qvalues[(state,action,t)]
                    if maxQ is None or Q > maxQ:
                        maxact = action
                        maxQ = Q
            return maxact
        
    def processEpisode(self, episode):     
        for t in range(len(episode)):
            (s, a, o) = episode[t]
            maxQ = None
           
            if t == self.env.getTimeHorizon()-1:
                self.Qvalues[(s,a,t)] = (1-self.alpha)*self.Qvalues[(s,a,t)]+ self.alpha*self.env.getReward(s,a,o)
                return
            else:
                for actionprime in range(self.env.getNumActions()): 
                    if self.env.isActionValid(s,actionprime) is True:
                        if self.env.getNextState(s,actionprime,o) is None:
                            val = 0
                        else:
                            val = self.Qvalues[(self.env.getNextState(s,actionprime,o),actionprime,t+1)]
                        if maxQ is None or maxQ < val: 
                            maxQ = val
                self.Qvalues[(s,a,t)] = (1-self.alpha)*self.Qvalues[(s,a,t)] + self.alpha*(self.env.getReward(s,a,o)+maxQ)
    
    def episodeStart(self):
        pass # is this right?
        
    """
    def Q(self, state, action , timestep, outcome): # needed to store the outcome i think
        if timestep == self.env.getTimeHorizon():
            self.Qvalues[(state,action,timestep)] =0
            return self.Qvalues[(state,action,timestep)]
        if (state,action,timestep) in self.Qvalues:
            return self.Qvalues[(state,action,timestep)]
        else:
            maxval = None
            for actionprime in range(self.env.getNumActions()):
                if self.env.isActionValid(state, actionprime) is True:
                    val = self.Q(self.env.getNextState(state, action, outcome), actionprime, timestep+1, outcome)
                    if maxval is None or val > maxval:
                        maxval = val
            self.Qvalues[(state,action,timestep)] = (1-self.alpha)*self.Q(state,action,timestep,outcome) + self.alpha*(self.env.getReward(state,action,outcome) + maxval)  
            return self.Qvalues[(state,action,timestep)]
    """
#Q4 Answer
"""Q learning is best made for extremely long term RL's. Its values only converge to the true Q values given correct Alpha and Gamma tuning and a long amount of time to converge to the correct Qvalues. Q values also need to take far more values than PSRL to get an equivalent regret""" 
