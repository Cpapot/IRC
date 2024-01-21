/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:37:08 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/20 14:21:54 by cpapot           ###   ########.fr       */
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
	std::cout << "\nServer closed." << std::endl;
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
		//mettre print error clean;
		std::cerr << "Fatal error: " << e.what() << '\n';
		return 1;
	}
	std::cout << "server Lauched" << std::endl;

	signal(SIGINT, handler);
	while (serv->getStatus())
	{
		serv->WaitForClient();
	}

}
