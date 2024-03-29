/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:29:19 by cprojean          #+#    #+#             */
/*   Updated: 2024/02/13 15:08:13 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_HPP
# define PRINT_HPP

# ifndef DEBUG
#  define DEBUG 0
# endif

# include <string>
# include <cstdarg>

namespace COLORS
{
	/*Typo*/
	const std::string bold		("\033[1m");
	const std::string italic	("\033[3m");
	const std::string underline	("\033[4m");
	/*Colors*/
	const std::string black("\033[30m");
	const std::string red("\033[31m");
	const std::string blue("\033[34m");
	const std::string green("\033[32m");
	const std::string white("\033[37m");
	const std::string beige("\033[223m");
	/*Reset*/
	const std::string reset		("\033[0m");
};

void	printShit(const char *str, ...);

#endif
