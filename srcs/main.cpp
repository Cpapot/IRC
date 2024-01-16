/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:37:08 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/16 18:01:33 by cpapot           ###   ########.fr       */
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
	serv = new server(argc, argv);

	signal(SIGINT, handler);
	while (serv->getStatus())
	{
		serv->WaitForClient();
	}

}
