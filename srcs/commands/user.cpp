/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:00:47 by cpapot            #+#    #+#             */
/*   Updated: 2024/02/17 13:30:48 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"

bool	testString(std::string str, std::string invalidChar);

bool	client::user(std::vector<std::string> splitLine)
{
	if (splitLine.size() != 5)
		return (sendToClient(ERR_NEEDMOREPARAMS(_nickname, "")), false);
	if (testString(splitLine[1], " &#\r\n\t\v") == false)
		return (sendToClient(ERR_NEEDMOREPARAMS(_nickname, "")), false);
	if (testString(splitLine[2], " &#\r\n\t\v") == false)
		return (sendToClient(ERR_NEEDMOREPARAMS(_nickname, "")), false);
	if (testString(splitLine[3], " &#\r\n\t\v") == false)
		return (sendToClient(ERR_NEEDMOREPARAMS(_nickname, "")), false);
	if (testString(splitLine[4], " &#\r\n\t\v") == false)
		return (sendToClient(ERR_NEEDMOREPARAMS(_nickname, "")), false);
	_username = splitLine[1];
	_hostname = splitLine[2];
	_servername = splitLine[3];
	_realname = splitLine[4];
	_realname.erase(0, 1);
	if (_nickname != "")
	{
		printShit("#d %s created his user. Welcome !", _username.c_str());
		sendToClient(std::string(RPL_USER(_nickname, _username, WELCOME_MSG)));
		_userAnswerSent = true;
		_hsDone = true;
	}
	return true;
}
