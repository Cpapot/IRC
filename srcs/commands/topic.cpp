/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 14:26:22 by cprojean          #+#    #+#             */
/*   Updated: 2024/02/19 17:23:19 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"

bool	client::topic(std::vector<std::string> splitLine)
{
	std::string topic;
	channel		*currentChannel;
	// bool		needOperator;

	if (splitLine.size() <= 1)
	{
		sendToClient(std::string(ERR_NOSUCHCHANNEL(_nickname, _username, "")));
		return false;
	}
	currentChannel = _serverPtr->getChannel(splitLine[1]);
	if (!currentChannel)
	{
		sendToClient(std::string(ERR_NOSUCHCHANNEL(_nickname, _username, splitLine[1])));
		return false;
	}
	if (currentChannel->isTopicOperator())
	{
		if (!currentChannel->isOperator(_clientSocket))
		{
			this->sendToClient(ERR_CHANOPRIVSNEEDED(_nickname, _username, splitLine[1]));
			return false;
		}
	}
	if (splitLine.size() >= 3)
	{
		if (!currentChannel->isOnChannel(_clientSocket))
		{
			sendToClient(ERR_NOTONCHANNEL(_nickname, _username, splitLine[1]));
			return false;
		}
		if (splitLine.size() == 3 && splitLine[2] == "::")
		{
			currentChannel->clearTopic();
			currentChannel->sendToAll(RPL_CLEARTOPIC(_nickname, _username, splitLine[1]));
			return true;
		}
		for (int i = 2; i < (int)splitLine.size(); i++)
		{
			topic += splitLine[i];
			if (i != (int)splitLine.size() - 1)
				topic += SPACE;
		}
		currentChannel->setTopic(topic, _nickname);
		currentChannel->sendToAll(RPL_TOPIC(_nickname, _username, splitLine[1], topic));
	}
	else
	{
		currentChannel->sendToAll(ERR_NEEDMOREPARAMS(_nickname, _username));
		return false;
	}
	return true;
}
