/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:00:03 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/21 21:43:45 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"

enum {CHANNEL_JOINNED = 0, ALREADY_LOGGED, NO_SUCH_SPACE, BADPASS, INVITE_ONLY};
bool	client::join(std::vector<std::string> splitLine)
{
	std::string	channelName;
	if (splitLine.size() <= 1)
	{
		sendToClient(std::string(ERR_NEEDMOREPARAMS(_nickname, _username)));
		return false;
	}
	if (splitLine[1][0] == '#')
		channelName = splitLine[1];
	else
	{
		sendToClient(std::string(ERR_NEEDMOREPARAMS(_nickname, _username)));
		return false;
	}
	_serverPtr->assosiateChannel(channelName, _clientSocket);
	switch (_serverPtr->getChannel(channelName)->newClient(this, splitLine))
	{
		case CHANNEL_JOINNED:
			_serverPtr->getChannel(channelName)->sendToAll(RPL_JOIN(_nickname, channelName));
			break;
		case ALREADY_LOGGED:
			sendToClient(std::string(ERR_UNKNOWNERROR(_nickname, _username, "Already log into channel")));
			return false;
		case BADPASS:
			sendToClient(ERR_BADCHANNELKEY(_nickname, _username, channelName));
			return false;
		case NO_SUCH_SPACE:
			sendToClient(ERR_CHANNELISFULL(_nickname, _username, channelName));
			return false;
		case INVITE_ONLY:
			sendToClient(ERR_INVITEONLYCHAN(_nickname, _username, channelName));
			return false;
	}
	_loggedChannel.push_back(channelName);
	/*std::string join = "JOIN : ";
	join += splitLine[1];
	new Print(join, MAGENTA, 3);*/
	return true;
}
