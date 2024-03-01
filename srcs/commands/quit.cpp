/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:00:43 by cpapot            #+#    #+#             */
/*   Updated: 2024/03/01 12:22:46 by cprojean         ###   ########.fr       */
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
	for (size_t i = 0; i != _loggedChannel.size(); i++)
		_serverPtr->getChannel(_loggedChannel[i])->disconnectClient(_clientSocket, 1, NULL);
	_serverPtr->deleteClientSocket(_clientSocket);
	std::string quit;
	for (unsigned long i = 1; i < splitLine.size(); i++)
		quit += splitLine[i] + SPACE;
	std::cout << _nickname << " is leaving from the server with the message: \"" << quit << "\"" << std::endl;
	printShit("#c %s left with the message : %s", _username.c_str(), quit.c_str());
	_serverPtr->sendToAllNetwork(RPL_QUIT(_nickname, _username, "c'est tchao"));
	delete this;
	return true;
}
