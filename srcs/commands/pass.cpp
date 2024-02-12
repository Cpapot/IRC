/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:00:36 by cpapot            #+#    #+#             */
/*   Updated: 2024/02/12 16:45:22 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"

bool	client::pass(std::vector<std::string> splitLine)
{
	_pass = splitLine[1];
	if (_pass.compare(_serverPtr->getPasswd()) != 0)
	{
		sendToClient(std::string(ERR_PASSWDMISMATCH(_nickname, _username)));
		return false;
	}
	sendToClient(std::string(":Logged\r\n"));
	printShit("#c caught password \"%s\"", _pass.c_str());
	_logged = true;
	return true;
}
