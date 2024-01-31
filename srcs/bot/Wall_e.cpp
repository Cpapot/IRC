/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wall_e.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:51:02 by cprojean          #+#    #+#             */
/*   Updated: 2024/01/31 13:24:14 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall_e.hpp"
#include "server.hpp"

void	wall_e::setAndCheckApiKey(void)
{

}

wall_e::wall_e(int clientSocket, server *serverPtr, char **argv)
{
	_pass = argv[2];
	_port = argv[1];
	_modeInvisible = true;
	_modeNotice = true;
	_modeWallops = true;
	_modeOperator = true;
	_logged = false;
	_username = "Wall-e";
	_nickname = "Wall-e";
	_hostname = "Wall-e";
	_servername = "";
	_realname = "";
	_clientSocket = clientSocket;
	_serverPtr = serverPtr;
}

wall_e::~wall_e(void)
{
	close(_clientSocket);
	return ;
}
