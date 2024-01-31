/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABot.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:06:26 by cprojean          #+#    #+#             */
/*   Updated: 2024/01/30 15:12:35 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Irc.hpp"

ABot::ABot(void)
{
	_nickname = "Random guy";
	return ;
}

ABot::ABot(int clientSocket, server *serverPtr, char **argv)
{
	_pass = argv[2];
	_port = argv[1];
	_modeInvisible = true;
	_modeNotice = true;
	_modeWallops = true;
	_modeOperator = true;
	_logged = false;
	_pass = "";
	_username = "Random Bot";
	_nickname = "Random Bot";
	_hostname = "Random Bot";
	_servername = "";
	_realname = "";
	_clientSocket = clientSocket;
	_serverPtr = serverPtr;
}

ABot::~ABot(void)
{
	close(_clientSocket);
	return ;
}
