/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firstHandShake.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:45:26 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/13 17:34:12 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"

bool	client::hsNick(std::vector<std::string> splitLine)
{
	//parse nickname (check if it contain " &#:\r\n\t\v")
	_nickname = splitLine[1];
	sendToClient(REPLY(_nickname, _realname, "NICK", _nickname));
	return true;
}

bool	client::hsUser(std::vector<std::string> splitLine)
{
	_username = splitLine[1];
	_hostname = splitLine[2];
	_servername = splitLine[3];
	_realname = splitLine[4];
	return true;
}

bool	client::hsPass(std::vector<std::string> splitLine)
{
	_pass = splitLine[1];
	return true;
}

bool	client::hsCap(void)
{
	sendToClient(REPLY(_nickname, _realname, "CAP", "Welcome To This Server!!"));
	return true;
}
