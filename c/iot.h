/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iot.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:19:54 by gzenner           #+#    #+#             */
/*   Updated: 2025/11/25 16:46:51 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_phone
{
	unsigned int	id;
	double			pos[2];
    bool            is_near;
}	t_phone;

typedef struct s_space
{
	unsigned int	startid;
	unsigned int	endid;
	unsigned int	phonescount;
	unsigned int	connectiondistance;
	unsigned int	limx;
	unsigned int	limy;
	unsigned int	iters;
}	t_space;
