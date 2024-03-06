/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:00:03 by cpapot            #+#    #+#             */
/*   Updated: 2024/03/06 16:00:15 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"

enum {CHANNEL_JOINNED = 0, ALREADY_LOGGED, NO_SUCH_SPACE, BADPASS, INVITE_ONLY};

void	client::joinInfo(std::string channel)
{
	if (_serverPtr->getChannel(channel)->getTopic() == "")
		sendToClient(RPL_NOTOPIC(_nickname, _username, channel));
	else
		sendToClient(RPL_TOPIC(_serverPtr->getChannel(channel)->getTopicSetter(), _username, channel, _serverPtr->getChannel(channel)->getTopic()));
	std::map<int, client *> map = _serverPtr->getChannel(channel)->getClientMap();
	for (std::map<int, client *>::iterator ite = map.begin(); ite != map.end(); ite++)
	{
		sendToClient(RPL_NAMREPLY(_nickname, _username, channel, ite->second->getNickname(), _serverPtr->getChannel(channel)->getUserStatus(ite->second->getSocket())));
		// std::cout << ite->second->getSocket() << std::endl;
	}
	sendToClient(RPL_ENDOFNAMES(_nickname, _username, channel));
}

bool	client::join(std::vector<std::string> splitLine)
{
	std::string	channelName;
	if (splitLine.size() <= 1)
	{
		sendToClient(std::string(ERR_NEEDMOREPARAMS(_nickname, _username)));
		// if (DEBUG)
		// printShit("#d %s tried to join a channel with wrong parameters", _username, channelName);
		return false;
	}
	if (splitLine[1][0] == '#')
		channelName = splitLine[1];
	else
	{
		sendToClient(std::string(ERR_NEEDMOREPARAMS(_nickname, _username)));
		// if (DEBUG)
		// 	printShit("#d %s tried to join a channel with wrong parameters", _username, channelName);
		return false;
	}
	_serverPtr->assosiateChannel(channelName, _clientSocket);
	switch (_serverPtr->getChannel(channelName)->newClient(this, splitLine))
	{
		case CHANNEL_JOINNED:
			_serverPtr->sendToAllNetwork(RPL_JOIN(_nickname, channelName));
			joinInfo(channelName);
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
	printShit("#c %s joined %s", _username.c_str(), channelName.c_str());
	return true;
}
