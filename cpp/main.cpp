/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:53:44 by gzenner           #+#    #+#             */
/*   Updated: 2025/11/25 17:06:28 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//the next idea is to allow to trace back how the phones connected
// and to find the most direct route
// the idea for the route is the following

#include <vector>
#include <iostream>
#include <random>
using namespace std;

typedef struct s_pos
{
	double	x;
	double	y;
	double	z;
}	t_pos;

class Phone
{
	private:
	unsigned int	id;
	t_pos			pos;
	vector<Phone *>	neighbours;
	
	public:
	Phone(unsigned int _id, unsigned int spread);

	unsigned int 	getId();
	t_pos 			getPos();
	void			addNeighbour(Phone *newneighbour);
	void			addNeighbours(vector<Phone *>newneighbours);
};


Phone::Phone(unsigned int _id, unsigned int spread)
{
	id = _id;
	pos.x = rand() % spread;
	pos.y = rand() % spread;
	pos.z = rand() % spread;
}

unsigned int	Phone::getId()
{
	return (id);
}

t_pos	Phone::getPos()
{
	return (pos);
}

void Phone::addNeighbour(Phone *newneighbour)
{
	neighbours.push_back(newneighbour);
}

void Phone::addNeighbours(vector<Phone *>newneighbours)
{
	int	i;

	i = -1;
	while (++i < newneighbours.size())
		neighbours.push_back(newneighbours[i]);
}

bool	goodDistance(Phone currentphone, Phone nearphone, double distanceLimit)
{
		int		x;
		int		y;
		int		z;
		double	distance;
		t_pos	nearPos;
		t_pos	currentPos;

		nearPos = nearphone.getPos();
		currentPos = currentphone.getPos();
		x = nearPos.x - currentPos.x;
		y = nearPos.y - currentPos.y;
		z = nearPos.z - currentPos.z;
		distance = (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
		return (distance <= distanceLimit);
}

bool idInArr(unsigned int id, vector<Phone *> arr)
{
	int	i;

	i = -1;
	while (++i < arr.size())
		if (arr[i]->getId() == id) return (true);
	return (false);
}

bool check_phone_in_neighbours(const vector<Phone *> &nearbyphones, unsigned int endid)
{
	int				i;
	t_pos			nearPos;

	i = -1;
	while (++i < nearbyphones.size())
	{
		if (nearbyphones[i]->getId() == endid)
		{
				nearPos = nearbyphones[i]->getPos();
				cout << "Found Phone at " << nearPos.x << " " << nearPos.y << "\n";
				return (true);
		}
	}
	return (false);
}

void printPhonePos(Phone phone)
{
	t_pos			currentPos;

	currentPos = phone.getPos();
	cout << "Printing Position:\nid : " << phone.getId() << " and Pos: " << currentPos.x << " " << currentPos.y << " " << currentPos.z << "\n";
}

bool	nearANYNearPhone(Phone currentPhone, const vector<Phone *> &nearbyphones, unsigned int maxDistance)
{
	int	i;

	i = -1;
	while (++i < nearbyphones.size())
	{
		if (goodDistance(currentPhone, *nearbyphones[i], maxDistance))
		{
			return (true);
		}
	}
	return (false);
}

void	trackpath(unsigned int startid, unsigned int endid, vector<Phone *> &phones, unsigned int maxDistance)
{
		int				i;
		unsigned int	iters;
		vector<Phone *> newphones;
		vector<Phone *> nearbyphones;

		iters = 0;
		printPhonePos(*phones[startid]);
		printPhonePos(*phones[endid]);
		nearbyphones.push_back(phones[startid]);
		while (!check_phone_in_neighbours(nearbyphones, endid))
		{
			i = -1;
			newphones.clear();
			cout << "iteration: " << ++iters << "\n";
			while (++i < phones.size())
			{
				if (!idInArr(phones[i]->getId(), nearbyphones) && nearANYNearPhone(*phones[i], nearbyphones, maxDistance))
				{
					newphones.push_back(phones[i]);
					phones.erase(phones.begin() + i); //this should remove that phone from phones and make next iterations faster.
					i--;
				}
			}
			if (newphones.size() == 0)
			{
				cout << "No new phones reachable and searched phone cannot be found\n";
				break;
			}
			else
			{
				i = -1;
				cout << newphones.size() << " new phones found.\n";
				while (++i < newphones.size())
				{
					nearbyphones.push_back(newphones[i]);
				}
			}
		}
}

void initPhones(int *i, vector<Phone *> &Phones, unsigned int limit, unsigned int spread)
{
	*i = -1;
	while (++(*i) < limit)
		Phones.push_back(new Phone(*i, spread));
}

void deletePhones(int i, vector<Phone *> &Phones)
{
	cout << "debug i:" << i << "\n";
	while (--i > -1)
		delete Phones[i];
}

int main(int ac, char **av)
{
	int					i;
	unsigned int		limit;
	unsigned int		spread;
	unsigned int		startid;
	unsigned int		endid;
	unsigned int		maxDistance;
	vector<Phone *>		Phones;

	i = -1;
	srand(time(NULL));
//	if (ac != 4) exit(1);
	limit = atoi(av[1]);
	spread = atoi(av[2]);
	startid = atoi(av[3]);
	endid = atoi(av[4]);
	maxDistance  = atoi(av[5]);
	initPhones(&i, Phones, limit, spread);
	trackpath(0, endid, Phones, maxDistance);
	deletePhones(i, Phones);
    return (0);
}
