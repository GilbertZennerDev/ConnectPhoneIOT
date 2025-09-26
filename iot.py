# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    iot.py                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/22 15:02:32 by gzenner           #+#    #+#              #
#    Updated: 2025/08/22 16:55:27 by gzenner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import random, math, sys

class Space:
	def __init__(self, phonescount, startid, searchedid, distance):
		self.startid = 	startid
		self.searchedid = searchedid
		self.phonescount = phonescount
		self.distance = distance
		self.checks()
		self.addphones()
		self.trackpath()

	def checks(self):
		c_badrange = lambda value: value < 0 or value >= self.phonescount 
		c_distance = lambda distance: distance < 0
		try:
			int(self.startid), int(self.searchedid), int(self.phonescount), int(self.distance)
		except Exception as e:
			print(e), exit()
		if c_badrange(self.startid) or c_badrange(self.searchedid):
			print('Bad Ids'), exit()
		if c_distance(self.distance):
			print('Bad Distance'), exit()
	def addphones(self):
		self.phones = [Phone(i) for i in range(self.phonescount)] 

	def trackpath(self):
		self.getneighbours()

	def getneighbours(self):
		near = lambda phone: abs(self.phones[self.startid].pos['x'] - phone.pos['x']) < self.distance and abs(self.phones[self.startid].pos['y'] - phone.pos['y']) < self.distance
		self.nearbyphones = set([phone for phone in self.phones if near(phone)])
		self.check_phone_in_neighbours()

	def check_phone_in_neighbours(self):
		for phone in self.nearbyphones:
			if phone.startid == self.startid: self.find_phone(), exit()
		return False
	    
	def getphonedata(self, searchedid):
		for phone in self.phones:
			id, posx, posy = phone.sendpos()
			if id == searchedid: return id, posx, posy

	def find_phone(self):
		id1, pos1x, pos1y = self.getphonedata(self.startid)
		id2, pos2x, pos2y = self.getphonedata(self.searchedid)
		print(id1, 'at pos', pos1x, pos1y, 'found', id2, 'at pos', pos2x, pos2y)

class Phone:
    def __init__(self, startid):
        self.startid = startid
        self.pos = {'x': random.randint(0, 1000), 'y': random.randint(0, 1000)}
    def sendpos(self):
        return self.startid, self.pos['x'], self.pos['x']

space = Space(10000, random.randint(0, 10000), random.randint(0, 10000), 1000)
