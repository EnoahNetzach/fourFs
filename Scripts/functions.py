print 43

import sys
from fourFs import *

def printHelp():
   ok = True
   print "help"


def checkIfExistsPixel(matrix, x, y):
   check = False
   if (x > 0 and x < matrix.width() and y > 0 and y < matrix.height()):
      check = True
   return check

def checDirection(direction, x, y, matrix):
   if (direction == 0):
      y -= 1
   if (direction == 1):
      x += 1
      y -= 1
   if (direction == 2):
      x += 1
   if (direction == 3):
      x += 1
      y += 1
   if (direction == 4):
      y += 1
   if (direction == 5):
      x -= 1
      y += 1
   if (direction == 6):
      x -= 1
   if (direction == 7):
      x -= 1
      y -= 1
   return checkIfExistsPixel(matrix, x, y), x, y

def moveUnit(unit, matrix, x, y):
   for pixel in unit.pixels():
      matrix.pixelAtIndex(pixel).removeUnit(unit.id())
      unit.removePixel(pixel)
   for pixel in matrix.pixelsAroundPosition(x, y, unit.radius):
      pixel.addUnit(unit.id())
      unit.addPixel(pixel.index())
   #
   # FIXME: sharedPixel assignment to unit's centralPixel 
   # works in C++, but doesn't seem to work here..
   #
   unit.centralPixel = matrix.pixelAtPosition(x, y).index()

def simulation(map, swarm):
   for unit in swarm.units():
      index = unit.second().centralPixel
      pos = map.matrix().positionFromIndex(index)
      x = pos.first()
      y = pos.second()
      # check if crowed or overcrowed
      ratio = 0 # @feed
      area = map.matrix().pixelsAroundIndex(index, 2)
      for p in area:
         ratio += p.nOfUnits()
      ratio /= len(area)
      if (ratio > 0.5): # @fly
         moved = False
         while not moved:
            x = pos.first()
            y = pos.second()
            direction = randInt(0, 7)
            moved, x, y = checDirection(direction, x, y, map.matrix())
         moveUnit(unit.second(), map.matrix(), x, y)
      # elif (ratio > 0.75): # @fight
      # else: # @mate
