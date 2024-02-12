/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:00:39 by cpapot            #+#    #+#             */
/*   Updated: 2024/02/12 16:46:01 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"

bool	server::ping(int clientSocket, std::vector<std::string> splitLine)
{
	if (splitLine.size() == 1)
	{
		_clientMap[clientSocket]->sendToClient(std::string(ERR_NOORIGIN(_clientMap[clientSocket]->getNickname(), _clientMap[clientSocket]->getUsername())));
		return false;
	}
	_clientMap[clientSocket]->sendToClient(RPL_PING(_clientMap[clientSocket]->getNickname(), _clientMap[clientSocket]->getUsername(), splitLine[1]));
	printShit("#d PONG");
	return true;
}
