/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:55:19 by gzenner           #+#    #+#             */
/*   Updated: 2025/11/25 17:08:40 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>

class Phone
{
    unsigned int    id;
    double          pos[2];
};

class IOT
{
    std::vector<Phone*> Phones;
    public:
        void initPhones(char **);
        void test();
};