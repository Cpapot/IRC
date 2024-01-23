/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:00:43 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/23 17:10:54 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"

bool	client::quit(std::vector<std::string> splitLine)
{
	splitLine[1].erase(0, 1);
	std::cout << _nickname << " is leaving from the server with the message: \"" << splitLine[1] << "\"" << std::endl;
	for (size_t i = 0; i != _loggedChannel.size(); i++)
	{
		_serverPtr->getChannel(_loggedChannel[i])->disconnectClient(_clientSocket);
	}
	_serverPtr->deleteClientSocket(_clientSocket);
	_serverPtr->sendToAllNetwork(RPL_QUIT(_nickname, _username, "c'est tchao"));
	delete this;
	return true;
}
