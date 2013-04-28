import sys
from fourFs import *

def printHelp():
	matrix = Matrix(10, 10)
	unit = Unit(1)
	''' 
	FIXME: sharedPixel assignment to unit's centralPixel 
			 works in C++, but doesn't seem to work here..
	'''
	unit.centralPixel(matrix.pixelAtPosition(4, 4))
	help(unit)
	print matrix.pixelAtPosition(4, 4).height, unit.centralPixel().height
	#help(fourFs.Matrix(0, 0))
	#help(fourFs.Pixel(1, False))

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
		pixel.removeUnit(unit)
		unit.removePixel(pixel)
	for pixel in matrix.pixelsAroundPosition(x, y, unit.radius):
		pixel.addUnit(unit)
		unit.addPixel(pixel)
	unit.centralPixel(matrix.pixelAtPosition(x, y))

def simulation(map, units):
	for unit in units:
		index = unit.centralPixel().index()
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
			moveUnit(unit, map.matrix(), x, y)
		# elif (ratio > 0.75): # @fight
		# 	fight = True # dummy
		# else: # @mate
		# 	mate = True # dummy
