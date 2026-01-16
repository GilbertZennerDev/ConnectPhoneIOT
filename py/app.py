# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    app.py                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/22 15:02:32 by gzenner           #+#    #+#              #
#    Updated: 2025/11/25 16:47:32 by gzenner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import random, math, sys
import matplotlib.pyplot as plt

class Space:
	def __init__(self, phonescount, startid, endid, distance, spread):
		self.startid = 	startid
		self.endid = endid
		self.phonescount = phonescount
		self.distance = distance
		self.limx = spread
		self.limy = spread
		self.iters = 0
		self.checks()
		self.addphones()
		#self.plotPhones(self.phones, 'green')
		self.trackpath()

	def checks(self):
		c_badrange = lambda value: value < 0 or value >= self.phonescount 
		c_distance = lambda distance: distance < 0
		try:
			self.startid = int(self.startid)
			self.endid = int(self.endid)
			self.phonescount = int(self.phonescount)
			self.distance = int(self.distance)
			self.limx = int(self.limx)
			self.limy = int(self.limy)
		except Exception as e:
			print(e); exit()
		if c_badrange(self.startid) or c_badrange(self.endid) or c_distance(self.distance):
			print('Bad Input'); exit()

	def addphones(self):
		self.phones = [Phone(i, random.randint(0, self.limx), random.randint(0, self.limy)) for i in range(self.phonescount)]

	def gooddistance(self, currentphone, nearphone):
		x = nearphone.pos['x'] - currentphone.pos['x']
		y = nearphone.pos['y'] - currentphone.pos['y']
		distance = math.sqrt(x**2+y**2)
		return distance <= self.distance
    
	def near(self, currentphone):
		for nearphone in self.nearbyphones:
			if self.gooddistance(currentphone, nearphone): return True
		return False

	def trackpath(self):
		samelen = lambda : len(self.nearbyphones) <= len(self.phones)
		self.nearbyphones = [self.phones[self.startid]]
		while not self.check_phone_in_neighbours() and samelen():
			self.iters += 1
			print("Iteration #", self.iters)
			self.newnearphones = [phone for phone in self.phones if phone not in self.nearbyphones and self.near(phone)]
			if not len(self.newnearphones) and not self.check_phone_in_neighbours():
				print('No new phones reachable and searched phone cannot be found'); exit()
			self.nearbyphones += self.newnearphones
			self.plotPhones()
			

	def check_phone_in_neighbours(self):			
		ids = [phone.id for phone in self.nearbyphones]
		if self.endid in ids: self.find_phone(); exit()
		if len(self.nearbyphones) >= self.phonescount:
			print('Phone not found'); exit()
	    
	def getphonedata(self, endid):
		for phone in self.phones:
			id, posx, posy = phone.sendpos()
			if id == endid: return id, posx, posy

	def find_phone(self):
		id1, pos1x, pos1y = self.getphonedata(self.startid)
		id2, pos2x, pos2y = self.getphonedata(self.endid)
		print(id1, 'at pos', pos1x, pos1y, 'found', id2, 'at pos', pos2x, pos2y, 'Iterations:', self.iters)
	
	def plotPhones(self):
		pos = [p.sendpos() for p in self.phones]
		x_start = [self.phones[self.startid].sendpos()[1]]
		y_start = [self.phones[self.startid].sendpos()[2]]
		x_end = [self.phones[self.endid].sendpos()[1]]
		y_end = [self.phones[self.endid].sendpos()[2]]
		x = [p[1] for p in pos]
		y = [p[2] for p in pos]
		x_newnear = [phone.sendpos()[1] for phone in self.newnearphones]
		y_newnear = [phone.sendpos()[2] for phone in self.newnearphones]		
		plt.scatter(x, y, color = 'black', marker='.')
		plt.scatter(x_newnear, y_newnear, color = 'green', marker='+')
		plt.scatter(x_start, y_start, color = 'blue', marker='$s$')
		plt.scatter(x_end, y_end, color = 'red',marker='$e$')
		plt.show()

class Phone:
    def __init__(self, id, x, y):
        self.id = id
        self.pos = {'x': x, 'y': y}
    def sendpos(self):
        return self.id, self.pos['x'], self.pos['y']

def run():
	if len(sys.argv) != 6: print('Usage:', sys.argv[0], 'phonecount', 'startid', 'endid', 'connectiondistance', 'spread'); exit()
	space = Space(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5])

if __name__ == "__main__": run()
