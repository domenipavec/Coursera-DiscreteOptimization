#!/usr/bin/python
# -*- coding: utf-8 -*-
# visualize with 

import math
from collections import namedtuple
import matplotlib.pyplot as plt

Point = namedtuple("Point", ['x', 'y'])

def length(point1, point2):
    return math.sqrt((point1.x - point2.x)**2 + (point1.y - point2.y)**2)

def visualize(input_data, order):
    # parse the input
    lines = input_data.split('\n')

    nodeCount = int(lines[0])

    points = []
    x = []
    y = []
    for i in range(1, nodeCount+1):
        line = lines[i]
        parts = line.split()
        points.append(Point(float(parts[0]), float(parts[1])))
        x.append(float(parts[0]))
        y.append(float(parts[1]))

    plt.plot(x,y,'bo')

    for i in range(len(order)):
        index1 = int(order[i-1])
        index2 = int(order[i])
        plt.arrow(x[index1], y[index1], x[index2] - x[index1], y[index2]-y[index1])

    plt.axis([min(x)-1,max(x)+1, min(y)-1,max(y)+1])

    plt.show()

import sys

if __name__ == '__main__':
    if len(sys.argv) > 1:
        file_location = sys.argv[1].strip()
        input_data_file = open(file_location, 'r')
        input_data = ''.join(input_data_file.readlines())
        input_data_file.close()
        visualize(input_data, sys.argv[2:])
    else:
        print 'This test requires an input file.  Please select one from the data directory. (i.e. python visualize.py ./data/tsp_51_1)'

