/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:05:43 by cprojean          #+#    #+#             */
/*   Updated: 2024/02/08 15:29:03 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "wall_e.hpp"
# include "print.hpp"
# include <stdlib.h>
# include <signal.h>

wall_e	*bot;

void handler(int s)
{
	bot->disconnectBot("Bot Stopped");
	delete bot;
	exit(s);
}

int main(int argc, char **argv)
{
	signal(SIGINT, handler);
	try
	{
		bot = new wall_e(argc, argv);
		bot->waitForServer();
	}
	catch(const std::exception& e)
	{
		printShit("#e Fatal error: %s", e.what());
	}
	//bot->disconnectBot("Bot Stopped");
	delete bot;
}
