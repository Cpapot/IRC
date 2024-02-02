/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:05:43 by cprojean          #+#    #+#             */
/*   Updated: 2024/02/02 12:10:59 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "wall_e.hpp"
# include "print.hpp"

wall_e	*bot;

int main(int argc, char **argv)
{
	try
	{
		bot = new wall_e(argc, argv);
	}
	catch(const std::exception& e)
	{
		printShit("#e Fatal error: %s", e.what());
		return 1;
	}
	bot->sendFirstHandShake();
	while (true)
	{
		bot->listenToServer();
	}
}
