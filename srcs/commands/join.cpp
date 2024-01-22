/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:00:03 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/20 18:00:20 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"

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
	_serverPtr->assosiateChannel(channelName);
	if (_serverPtr->getChannel(channelName)->newClient(this) == 1)
	{
		sendToClient(std::string(ERR_UNKNOWNERROR(_nickname, _username, "Already log into channel")));
		return false;
	}
	_loggedChannel.push_back(channelName);
	/*std::string join = "JOIN : ";
	join += splitLine[1];
	new Print(join, MAGENTA, 3);*/
	return true;
}
