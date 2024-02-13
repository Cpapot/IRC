/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:00:47 by cpapot            #+#    #+#             */
/*   Updated: 2024/02/12 16:45:44 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"

bool	client::user(std::vector<std::string> splitLine)
{
	// if (testString(splitLine[1]) == false)
	// 	return(sendToClient(std::string("Le user il pue sa mere")), false);
	// if (testString(splitLine[2]) == false)
	// 	return(sendToClient(std::string("Le hostname il pue sa mere")), false);
	// if (testString(splitLine[3]) == false)
	// 	return(sendToClient(std::string("The server name has an incorrect character")), false);
	// if (testString(splitLine[4]) == false)
	// 	return(sendToClient(std::string("This real name has an incorrect character")), false);
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
	}
	return true;
}
