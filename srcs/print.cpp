/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:29:20 by cprojean          #+#    #+#             */
/*   Updated: 2024/01/21 17:20:34 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.hpp"
#include <iostream>
#include <string.h>

using namespace COLORS;

void	whatsThisShit(std::va_list variadic, char c)
{
	switch(c)
	{
		case 's' :
			std::cout << va_arg(variadic, char *);
			break;
		case 'c' :
			std::cout << va_arg(variadic, int);
			break;
		case 'd' :
			std::cout << va_arg(variadic, int);
			break;
		case '%' :
			std::cout << '%';
			break;
	}
}

void	whatsTheMode(char c)
{
	switch(c)
	{
		case 'e' :
			std::cout << underline << bold << red << "[ ERROR ]" << reset;
			break;
		case 'd' :
			std::cout << bold << red << "[ DEBUG ]" << reset;
			break;
		case 'c' :
			std::cout << bold << beige << "[ COMMAND ]" << reset;
			break;
		case 'i' :
			std::cout << underline << green << "[ INFO ]" << reset;
			break;
	}
}

void	printShit(const char *str, ...)
{
	std::va_list variadic;
	
	va_start(variadic, str);
	for(size_t i = 0; i < strlen(str); i++)
	{
		if (i == 0 && str[i] == '#')
		{
			i++;	
			whatsTheMode(str[i]);
		}
		else if (str[i] == '%')
		{
			i++;
			whatsThisShit(variadic, str[i]);
		}
		else
			std::cout << str[i];
	}
	va_end(variadic);
}

void debugUser()
{
	printShit("#d ")
}