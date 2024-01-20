/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:29:20 by cprojean          #+#    #+#             */
/*   Updated: 2024/01/19 17:59:40 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.hpp"
#include <stdio.h>

Print::Print( std::string message, unsigned long color, int mode )
{
	if (mode == 0)	
		printf("\033[1;%lum[MESSAGE] : %s\033[0m\n", color, message.c_str());
	if (mode == 1)
		printf("\033[1;%lum[ERROR] : %s\033[0m\n", color, message.c_str());
	if (mode == 2)
		printf("\033[1;%lum[INFO] : %s\033[0m\n", color, message.c_str());
	if (mode == 3)
		printf("\033[1;%lum[CMD] %s\033[0m\n", color, message.c_str());
	
}

Print::~Print()
{
}
