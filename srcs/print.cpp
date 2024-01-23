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

void	printStr(const char *str, const char *base, int mode);

void	whatsThisShit(std::va_list variadic, const char *str, int i)
{
	switch(str[i])
	{
		case 's' :
			printStr(va_arg(variadic, char *), str, 0);
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
			std::cerr << bold << red << "[ DEBUG ]" << reset;
			break;
		case 'c' :
			std::cout << bold << beige << "[ COMMAND ]" << reset;
			break;
		case 'i' :
			std::cout << underline << green << "[ INFO ]" << reset;
			break;
	}
}

void	recursivShit(const char *str, const char *base, int i)
{
	std::string newString;
	std::cout << std::endl;
	newString += base[0];
	newString += base[1];
	newString += ' ';
	newString += &str[i + 1];
	printStr(newString.c_str(), base, 1);
}

void	printStr(const char *str, const char *base, int mode)
{
	for(size_t i = 0; i < strlen(str); i++)
	{
		if (str[i] == '#' && i == 0 && mode == 1)
		{
			i++;
			whatsTheMode(str[i]);
			i++;
		}
		else if(str[i] == '\n' && i != strlen(str) - 1 && i != strlen(str))
		{
			recursivShit(str, base, i);
			return ;
		}
		else if (str[i] == '\n' && (i == strlen(str) || i == strlen(str) - 1))
			i++;
		else
			std::cout << str[i];
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
			whatsThisShit(variadic, str, i);
		}
		else if (str[i] == '\n' && i != strlen(str) - 1)
		{
			recursivShit(str, str, i);
			std::cout << std::endl;
			return ;
		}
		else
			std::cout << str[i];
	}
	std::cout << std::endl;
	va_end(variadic);
}
