# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for 
# educational purposes provided that (1) you do not distribute or publish 
# solutions, (2) you retain this notice, and (3) you provide clear 
# attribution to UC Berkeley, including a link to 
# http://inst.eecs.berkeley.edu/~cs188/pacman/pacman.html
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero 
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and 
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

def scoreEvaluationFunction(currentGameState):
    """
      This default evaluation function just returns the score of the state.
      The score is the same one displayed in the Pacman GUI.

      This evaluation function is meant for use with adversarial search agents.
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
      This class provides some common elements to all of your
      multi-agent searchers.  Any methods defined here will be available
      to the MinimaxPacmanAgent & AlphaBetaPacmanAgent.

      You *do not* need to make any changes here, but you can if you want to
      add functionality to all your adversarial search agents.  Please do not
      remove anything, however.

      Note: this is an abstract class: one that should not be instantiated.  It's
      only partially specified, and designed to be extended.  Agent (game.py)
      is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)


class MinimaxAgent(MultiAgentSearchAgent):
    """
      Your minimax agent (question 1)
    """
    def getMin(self, gameState, depth, ghost):
        if gameState.isWin() or gameState.isLose(): 
            return (self.evaluationFunction(gameState), None)
        minVal = None 
        minAction = None
        for action in gameState.getLegalActions(ghost):
            nextState =gameState.generateSuccessor(ghost, action) 
            if ghost == gameState.getNumAgents()-1:
                val, mact = self.getMax(nextState,depth)
                if minVal is None or val < minVal:
                    minVal = val
                    minAction = action
            else: 
                val, mact = self.getMin(nextState,depth,ghost+1)
                if minVal is None or val < minVal:
                    minVal = val
                    minAction = action 
        return minVal, minAction

    def getMax(self, gameState, depth):
        if gameState.isWin() or gameState.isLose() or depth == self.depth: 
            return (self.evaluationFunction(gameState),None)
        depth += 1
        maxVal = None 
        maxAction =None
        player = 0 
        for action in gameState.getLegalActions(player):
            nextState =gameState.generateSuccessor(player, action)
            val, mact = self.getMin(nextState, depth, 1) 
            if maxVal is None or val > maxVal:
                maxVal = val
                maxAction = action
        return maxVal, maxAction

    def getAction(self, gameState):
        """
          Returns the minimax action from the current gameState using self.depth
          and self.evaluationFunction.
        """
        "*** YOUR CODE HERE ***"
      
        player = 0
        score, action = self.getMax(gameState,0)
        return action
       

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
      Your minimax agent with alpha-beta pruning (question 2)
    """

    """
    BIG NOTE
    I initially tried to make alpha,beta, None and try to do the 
    "if alpha is None or etc.."
    and it broke, but when i made them inf,-inf, it worked immediatly. 
    """

    def getMin(self, gameState, depth, ghost, alpha, beta):
        if gameState.isWin() or gameState.isLose(): 
            return (self.evaluationFunction(gameState), None)
        minVal = None 
        minAction = None
        for action in gameState.getLegalActions(ghost):
            nextState =gameState.generateSuccessor(ghost, action) 
            if ghost == gameState.getNumAgents()-1:
                val, mact = self.getMax(nextState,depth, alpha, beta)
                if minVal is None or val < minVal:
                    minVal = val
                    minAction = action
                if  minVal < alpha:
                    return minVal, minAction
                if beta > minVal:
                    beta = minVal 
            else: 
                val, mact = self.getMin(nextState,depth,ghost+1, alpha, beta)
                if minVal is None or val < minVal:
                    minVal = val
                    minAction = action  
                if minVal < alpha:
                    return minVal, minAction
                if beta > minVal:
                    beta = minVal 
        
        return minVal, minAction

    def getMax(self, gameState, depth, alpha, beta):
        if gameState.isWin() or gameState.isLose() or depth == self.depth: 
            return (self.evaluationFunction(gameState),None)
        depth += 1
        maxVal = None 
        maxAction =None
        player = 0 
        for action in gameState.getLegalActions(player):
            nextState =gameState.generateSuccessor(player, action)
            val, mact = self.getMin(nextState, depth, 1, alpha, beta)
            if maxVal is None or val > maxVal:
                maxVal = val
                maxAction = action
            if maxVal > beta:
                return maxVal, maxAction
            if alpha < maxVal:
                alpha = maxVal
        return maxVal, maxAction

    def getAction(self, gameState):
        """
          Returns the minimax action from the current gameState using self.depth
          and self.evaluationFunction.
        """
        "*** YOUR CODE HERE ***"
        from math import inf
        alpha = -inf
        beta = inf 
        player = 0
        score, action = self.getMax(gameState, 0, alpha, beta)
        return action


def betterEvaluationFunction(currentGameState):
    """
      Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
      evaluation function (question 3).

      DESCRIPTION:
        First, I look at where I am, where the food is, how much ive eaten, where the ghosts are, the number of times ive scared them, and how much score i have
        All distance between points is done by manhattanDistance because it is the easiest. 
        I take the reciprical of the sum distance to food +1 (in case for some reason that number is zero), And then I add up all the elements I consider positive (reciprical of distance to food, my current score, the number of times i scared a ghost) and minus it by what i consider negative( how close the ghosts are)

    """
    "*** YOUR CODE HERE ***"
    Position = currentGameState.getPacmanPosition()
    TotalFood = currentGameState.getFood()
    CurScore = currentGameState.getScore()
    Eaten = len(TotalFood.asList(False))
    FoodLeft = TotalFood.asList()
    Ghosts = currentGameState.getGhostStates()
    Scared = [currentState.scaredTimer for currentState in Ghosts]
    distance_to_food = []
    for food in FoodLeft:
        distance_to_food.append(1.0/(manhattanDistance(Position, food)+1))
    distance_to_ghost = []
    for ghost in Ghosts:
        distance_to_ghost.append(manhattanDistance(Position,ghost.getPosition()))
    score = 0
    score += CurScore + sum(distance_to_food) + sum(Scared) - sum(distance_to_ghost) + Eaten  
    return score
# Abbreviation
better = betterEvaluationFunction

