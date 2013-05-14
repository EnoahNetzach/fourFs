import sys
from fourFs import *

def printHelp():
   ok = True

def moveUnit(unit, matrix, index):
   for pixel in unit.pixels():
      p = matrix.pixelAtIndex(pixel)
      p.removeUnit(unit.id())
      unit.removePixel(pixel)
   for pixel in matrix.pixelsAroundIndex(index, unit.radius):
      pixel.addUnit(unit.id())
      unit.addPixel(pixel.index())
   unit.centralPixel = index

def simulation(map, swarm):
   for unitPair in swarm.units():
      unit = unitPair.second()
      index = unit.centralPixel
      matrix = map.matrix()
      pos = matrix.positionFromIndex(index)
      x = pos.first()
      y = pos.second()
      # check if crowed or overcrowed
      ratio = 0 # @feed
      area = matrix.pixelsAroundIndex(index, 2)
      for pixelInField in area:
         ratio += pixelInField.nOfUnits()
         positions = []
         for pixelInArea in matrix.pixelsAroundIndex(pixelInField.index(), unit.radius):
            positions.append([pixelInArea.nOfUnits(), pixelInArea.index()])
      ratio /= len(area)
      if (ratio > 0.5): # @fly
         # chose the best direction
         moveIndex = min(positions)[1]
         if moveIndex != index:
           print index, "->", moveIndex
           moveUnit(unit, matrix, moveIndex)
      # elif (ratio > 0.75): # @fight
      # else: # @mate
