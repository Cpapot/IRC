/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:37:08 by cpapot            #+#    #+#             */
/*   Updated: 2024/02/02 18:09:07 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include "server.hpp"
#include "client.hpp"
#include <signal.h>

server	*serv;

void handler(int s)
{
	delete serv;
	exit(s);
}

int main(int argc, char **argv)
{
	try
	{
		serv = new server(argc, argv);
	}
	catch(const std::exception& e)
	{
		printShit("#e Fatal error: %s", e.what());
		return 1;
	}
	signal(SIGINT, handler);
	while (serv->getStatus())
	{
		serv->WaitForClient();
	}

}
