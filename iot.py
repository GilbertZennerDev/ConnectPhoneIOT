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
		self.iters = 0
		self.checks()
		self.addphones()
		self.trackpath()

	def checks(self):
		c_badrange = lambda value: value < 0 or value >= self.phonescount 
		c_distance = lambda distance: distance < 0
		try:
			self.startid = int(self.startid)
			self.searchedid = int(self.searchedid)
			self.phonescount = int(self.phonescount)
			self.distance = int(self.distance)
		except Exception as e:
			print(e), exit()
		if c_badrange(self.startid) or c_badrange(self.searchedid) or c_distance(self.distance):
			print('Bad Input'), exit()	
	def addphones(self):
		self.phones = [Phone(i) for i in range(self.phonescount)] 

	def trackpath(self):
		near = lambda currentphone, startphone: abs(startphone.pos['x'] - currentphone.pos['x']) < self.distance or abs(startphone.pos['y'] - currentphone.pos['y']) < self.distance
		self.nearbyphones = []
		startphone = self.phones[self.startid]
		while not self.check_phone_in_neighbours():
			self.nearbyphones = set([phone for phone in self.phones if near(phone, startphone)])
			self.iters += 1
			print(self.nearbyphones)

	def check_phone_in_neighbours(self):			
		ids = [phone.id for phone in self.nearbyphones]
		for phone in self.nearbyphones:
			if phone.id == self.startid: self.find_phone(), exit()
		if len(self.nearbyphones) >= self.phonescount:
			print('Phone not found'), exit()
	    
	def getphonedata(self, searchedid):
		for phone in self.phones:
			id, posx, posy = phone.sendpos()
			if id == searchedid: return id, posx, posy

	def find_phone(self):
		id1, pos1x, pos1y = self.getphonedata(self.startid)
		id2, pos2x, pos2y = self.getphonedata(self.searchedid)
		print(id1, 'at pos', pos1x, pos1y, 'found', id2, 'at pos', pos2x, pos2y, 'Iterations:', self.iters)

class Phone:
    def __init__(self, id):
        self.id = id
        self.pos = {'x': random.randint(0, 1000), 'y': random.randint(0, 1000)}
    def sendpos(self):
        return self.id, self.pos['x'], self.pos['x']

def run():
	if len(sys.argv) != 5: print('Usage:', sys.argv[0], 'phonecount', 'startid', 'searchedid', 'connectiondistance'), exit()
	space = Space(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])
run()

'''
distance = 500
near = lambda currentphone, startphone: abs(startphone.pos['x'] - currentphone.pos['x']) < distance or abs(startphone.pos['y'] - currentphone.pos['y']) < distance
p1 = Phone(1)
p2 = Phone(2)
id1, pos1x, pos1y = p1.sendpos()
id2, pos2x, pos2y = p2.sendpos()
print(id1, pos1x, pos1y)
print(id2, pos2x, pos2y)
print(near(p1, p2))
'''
