#!/usr/bin/python

import sys
import networkx as nx
import matplotlib.pyplot as plt

ANTS    = 0
ROOMS   = 1
LINKS   = 2
EMPTY   = 3
MOVES   = 4

ERROR   = -1
FAILURE = 0
SUCCESS = 1

class Data:

    def __init__(self):
        self.flag = ANTS
        self.ants = 0
        self.rooms = list()
        self.links = list()
        self.moves = list()
        self.g = nx.Graph()

    def get_room(self, line):
        line = line.split(' ')
        if (len(line) != 3):
            self.flag += 1
            return FAILURE
        self.rooms.append(line[0])
        return SUCCESS

    def get_link(self, line):
        line = line.split('-')
        if (len(line) != 2):
            self.flag += 1
            return FAILURE
        self.links.append(line)
        return SUCCESS

    def get_move(self, line):
        self.moves.append(line)
        return SUCCESS

    def process(self, line):
        if (line.find('#') != -1):
            return
        if (self.flag == ANTS):
            self.ants = line
            self.flag += 1
            return SUCCESS
        if (self.flag == ROOMS):
            if (self.get_room(line) == SUCCESS):
                return SUCCESS
        if (self.flag == LINKS):
            if (self.get_link(line) == SUCCESS):
                return SUCCESS
        if (self.flag == EMPTY):
                self.flag += 1
                return SUCCESS
        if (self.flag == MOVES):
            if (self.get_move(line) == SUCCESS):
                return SUCCESS
    
    def toString(self):
        print('flag = ', self.flag)
        print('nb ants = ', self.ants)
        print('nb rooms = ', len(self.rooms))
        print('nb links', len(self.links))
        print('nb moves', len(self.moves))
        return SUCCESS

# Output from lem-in
li = sys.stdin.readlines()
data = Data()
for line in li:
    data.process(line.rstrip())
data.toString()

# Graph
print("Adding nodes...")
data.g.add_nodes_from(data.rooms)
print("Adding edges...")
for link in data.links:
    data.g.add_edge(link[0], link[1])
print("Drawing...")
nx.draw(data.g, with_labels=True)
print("Displaying...")
plt.show()