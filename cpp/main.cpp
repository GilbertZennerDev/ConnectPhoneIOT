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

class Phone
{
	public:
	Phone(unsigned int id);
    unsigned int	id;
    double          pos[2];
};

Phone::Phone(unsigned int id)
{
	id = id;
	pos[0] = rand() % 1000;
	pos[1] = rand() % 1000;
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
    return (0);
}
