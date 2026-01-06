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

/*
#include "IOT.hpp"

void IOT::test()
{
    std::cout << "Test successful.\n";
}

void IOT::initPhones(char **av)
{
	int i;
    unsigned int limit = atoi(av[1]);    

	i = -1<
    while (++i < limit)
        IOT::Phones.push_back(new Phone());
}
*/

#include <vector>
#include <iostream>
#include <random>
using namespace std;

typedef struct s_pos
{
	double x;
	double y;
}	t_pos;

class Phone
{
	public:
	Phone(unsigned int _id);
    unsigned int	id;
//    t_pos			pos;
    double          pos[2];
};

Phone::Phone(unsigned int _id)
{
	id = _id;
	pos[0] = rand() % 1000;
	pos[1] = rand() % 1000;
}

bool goodDistance(Phone currentphone, Phone nearphone, double distanceLimit)
{
		int		x;
		int		y;
		double	distance;
//		x = nearphone.pos['x'] - currentphone.pos['x']
//		y = nearphone.pos['y'] - currentphone.pos['y']
		x = nearphone.pos[0] - currentphone.pos[0];
		y = nearphone.pos[1] - currentphone.pos[1];
		distance = (sqrt(x * x + y * y));
		return (distance <= distanceLimit);
}

bool idInArr(unsigned int id, vector<Phone *> arr)
{
	int	i;

	i = -1;
	while (++i < arr.size())
		if (arr[i]->id == id) return (true);
	return (false);
}

bool check_phone_in_neighbours(vector<Phone *> nearbyphones, unsigned int endid)
{
	int				i;

	i = -1;
	while (++i < nearbyphones.size())
	{
		if (nearbyphones[i]->id == endid)
		{
				cout << "Found Phone at " << nearbyphones[i]->pos[0] << " " << nearbyphones[i]->pos[1] << "\n";
				return (true);
		}
	}
	return (false);
}

void printPhonePos(Phone phone)
{
	cout << "Printing Position:\nid : " << phone.id << " and Pos: " << phone.pos[0] << " " << phone.pos[1] << "\n";
}

bool	nearANYNearPhone(Phone currentPhone, vector<Phone *> nearbyphones, unsigned int maxDistance)
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

void	trackpath(unsigned int startid, unsigned int endid, vector<Phone *> phones)
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
				if (!idInArr(phones[i]->id, nearbyphones) && nearANYNearPhone(*phones[i], nearbyphones, 10))
				{
					newphones.push_back(phones[i]);
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

int main(int ac, char **av)
{
	int					i;
	unsigned int		limit;
	vector<Phone *>		Phones;

	i = -1;
	srand(time(NULL));
	if (ac != 2) exit(1);
	limit = atoi(av[1]);
	while (++i < limit)
		Phones.push_back(new Phone(i));
	trackpath(0, 2, Phones);
	while (--i > -1)
		delete (Phones[i]);
    return (0);
}
