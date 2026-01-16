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

//============================================================

typedef struct s_data
{
	unsigned int		limit;
	unsigned int		spread;
	unsigned int		startid;
	unsigned int		endid;
	unsigned int		maxDistance;
	vector<Phone *>		phones;
}	t_data;

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

void	trackpath(t_data &data)
{
		int				i;
		unsigned int	iters;
		vector<Phone *> newphones;
		vector<Phone *> nearbyphones;

		iters = 0;
		printPhonePos(*data.phones[data.startid]);
		printPhonePos(*data.phones[data.endid]);
		nearbyphones.push_back(data.phones[data.startid]);
		while (!check_phone_in_neighbours(nearbyphones, data.endid))
		{
			i = -1;
			newphones.clear();
			cout << "iteration: " << ++iters << "\n";
			while (++i < data.phones.size())
			{
				if (!idInArr(data.phones[i]->getId(), nearbyphones) && nearANYNearPhone(*data.phones[i], nearbyphones, data.maxDistance))
				{
					newphones.push_back(data.phones[i]);
					data.phones.erase(data.phones.begin() + i);
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
		/*i = -1;
		while (++i < nearbyphones.size() - 1)
		{
			delete nearbyphones[i];
		}
		i = -1;
		while (++i < newphones.size() - 1)
		{
			delete newphones[i];
		}*/
}

void initPhones(t_data &data)//vector<Phone *> &Phones, unsigned int limit, unsigned int spread)
{
	int i;

	i = -1;
	data.phones.clear();
	while (++i < data.limit)
		data.phones.push_back(new Phone(i, data.spread));
}

void deletePhones(vector<Phone *> &Phones)
{
	int i;

	i = -1;
	while (++i < Phones.size() - 0)
		delete Phones[i];
}

bool checks(int ac, char **av, t_data &data)
{
	bool error;

	try{
		data.limit = atoi(av[1]);
		data.startid = atoi(av[2]);
		data.endid = atoi(av[3]);
		data.maxDistance  = atoi(av[4]);
		data.spread = atoi(av[5]);
		error = false;
		if (data.limit < 2) error = true;
		if (data.startid < 0 || data.startid > data.limit - 1) error = true;
		if (data.endid < 0 || data.endid > data.limit - 1) error = true;
		if (data.maxDistance <= 0) error = true;
		if (data.spread <= 0) error = true;
		if (error) cout << "Error found.\n";
		if (error) return (false);
	}
	catch(exception e)
	{
		cout << "Error" << "\n";
		return (false);
	}
	return (true);
}

int main(int ac, char **av)
{
	t_data				data;

	srand(time(NULL));
	if (ac != 6){ cout << "Usage: " << av[0] << " phonecount startid endid connectiondistance spread"; return (1);};
	if (!checks(ac, av, data)) return (1);
	initPhones(data);
	trackpath(data);
	deletePhones(data.phones);
    return (0);
}
