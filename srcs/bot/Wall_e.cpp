/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wall_e.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:51:02 by cprojean          #+#    #+#             */
/*   Updated: 2024/01/30 13:56:01 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Irc.hpp"

Wall_e::Wall_e(int clientSocket, server *serverPtr, char **argv)
{
	_pass = argv[2];
	_port = argv[1];
	_modeInvisible = true;
	_modeNotice = true;
	_modeWallops = true;
	_modeOperator = true;
	_logged = false;
	_pass = "";
	_username = "Wall-e";
	_nickname = "Wall-e";
	_hostname = "Wall-e";
	_servername = "";
	_realname = "";
	_clientSocket = clientSocket;
	_serverPtr = serverPtr;
}

Wall_e::~Wall_e(void)
{
	close(_clientSocket);
	return ;
}