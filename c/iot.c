/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   iot.c											  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gzenner <gzenner@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/11/25 13:19:07 by gzenner		   #+#	#+#			 */
/*   Updated: 2025/11/25 15:29:23 by gzenner		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "iot.h"

void	ft_init_space(t_space *space, char **av)
{
	space->phonescount = atoi(av[1]);
	space->startid = atoi(av[2]);
	space->endid = atoi(av[3]);
	space->connectiondistance = atoi(av[4]);
	space->limx = atoi(av[5]);
	space->limy = atoi(av[6]);
	space->iters = 0;
}

void	ft_init_phones(t_phone **phones, t_phone **nearphones, t_space space)
{
	unsigned int	i;

	*phones = malloc(sizeof(t_phone) * space.phonescount);
	if (!phones)
		return ;
	*nearphones = malloc(sizeof(t_phone) * space.phonescount);
	i = 0;
	while (i < space.endid + 1)
	{
		(*phones)[i].id = i;
		(*phones)[i].pos[0] = random() % space.limx;
		(*phones)[i].pos[1] = random() % space.limy;
		(*phones)[i].is_near = false;
		(*nearphones)[i].id = 999999;
		++i;
	}
	(*phones)[space.startid].is_near = true;
	(*phones)[space.endid].is_near = true;
}

/*
def trackpath(self):
		samelen = lambda : len(self.nearbyphones) <= len(self.phones)
		self.nearbyphones = [self.phones[self.startid]]
		while not self.check_phone_in_neighbours() and samelen():
			self.iters += 1
			print(self.iters)
			newnearphones = [phone for phone in self.phones if phone not in self.nearbyphones and self.near(phone)]
			print('newphones', len(newnearphones))
			if not len(newnearphones) and not self.check_phone_in_neighbours():
				print('No new phones reachable and searched phone cannot be found'); exit()
			self.nearbyphones += newnearphones
*/

bool	ft_get_distance(double xp1, double xp2, double yp1, double yp2, t_space space)
{
	return (sqrt((yp1 - yp2)*(yp1 - yp2) + (xp1 - xp2)*(xp1 - xp2)) < space.connectiondistance);
}

bool	check_phone_in_neighbours(t_phone **phones, unsigned int count, unsigned int endid)
{
	unsigned int	i;

	i = 0;
	while (i < count)
	{
		if ((*phones)[i].id == endid)
		{
			(*phones)[i].is_near = true;
			printf("%d\n", (*phones)[i].is_near);
			return (true);
		}
		++i;
	}
	return (false);
}

bool	searched_phone_found(t_phone *phones, unsigned int count, unsigned int searchedid)
{
	unsigned int	i;

	i = 0;
	while (i < count)
	{
		if (phones->id == searchedid)
		{
			return (true);
		}
		++i;
	}
}

void	add_near_phones(t_phone **phones, t_phone **nearphones, t_space space)
{
	unsigned int	i;
	unsigned int	j;
	double			xp1;
	double			xp2;
	double			yp1;
	double			yp2;

	i = 0;
	while (i < space.phonescount)
	{
		printf("Debug i %d.\n", i);
		if ((*phones)[i].is_near)
		{
			j = 0;
			while (j < count)
			{
				printf("Debug j %d.\n", j);
				if (!((*phones)[j].is_near) && j != i)
				{
					xp1 = (*phones)[i].pos[0];
					xp2 = (*phones)[j].pos[0];
					yp1 = (*phones)[i].pos[1];
					yp2 = (*phones)[j].pos[1];
					if (ft_get_distance(xp1, xp2, yp1, yp2, space))
					{
						(*phones)[j].is_near = true;
						printf("Added id %d.\n", j);
						//break;
					}
				}
				++j;
			}
		}
		++i;
	}
}

void	trackpath(t_space space, t_phone **phones)
{
	/*the logic is quite simple: for all nearbyphones, browse across all the phones and add those which are near.
	repeat until searched phone is found or no more new phones are reachable
	the challenge is to determine which phones are not yeat i
	*/

	nearphones = malloc(sizeof(t_phone *) * space.phonescount);
	while(!searched_phone_found(*phones, space.phonescount, space.endid))
	{
		add_near_phones(phones, nearphones, space);
		printf("Searching %d.\n", space.endid);
		break;	
	}
	printf("Phone found!\n");
	free(newphones);
}
			
int	main(int ac, char **av)
{
	t_space space;
	t_phone *phones;
	t_phone	*nearphones;

	if (ac != 7)
	{
		printf("Usage: %s phonecount startid endid connectiondistance limx limy/\n", av[0]);
		return (0);
	}
	ft_init_space(&space, av);
	ft_init_phones(&phones, &nearphones, space);
	trackpath(space, &phones);
	free(phones);
	return (0);
}