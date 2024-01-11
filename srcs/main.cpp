/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:37:08 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/11 17:06:39 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include "server.hpp"
#include "client.hpp"

int main(int argc, char **argv)
{
	server	serv(argc, argv);
	while (serv.getStatus())
	{
			client(serv.acceptClient());
	}

}
