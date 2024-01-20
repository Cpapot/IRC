/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:52:46 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/20 18:03:56 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"

enum {CAP = 0, PASS, PING, QUIT, NICK, USER, PART, MODE, JOIN, PRIVMSG};

bool	client::parseCommand(size_t splitIndex, size_t commandIndex, std::vector<std::string> split)
{
	std::vector<std::string>	splitLine;
	tokenize(split[splitIndex], ' ', splitLine);
	if (commandIndex >= 3 && _logged != true)
	{
		sendToClient(std::string(ERR_NOTREGISTERED(_nickname, _username)));
		return false;
	}
	switch (commandIndex)
	{
	case CAP:
		return cap();
	case PASS:
		return pass(splitLine);
	case NICK:
		return nick(splitLine);
	case USER:
		return user(splitLine);
	case PING:
		return _serverPtr->ping(_clientSocket, splitLine);
	case QUIT:
		return quit(splitLine);
	case PART:
		return part(splitLine);
	case MODE:
		return mode(splitLine);
	case JOIN:
		return join(splitLine);
	case PRIVMSG:
		return privmsg(splitLine);
	}
	return false;
}

void	client::findCommand(char buffer[CLIENTBUFFERSIZE])
{
	std::vector<std::string>	split;
	std::string	commandList[10] = {"CAP", "PASS", "PING", "QUIT", "NICK", "USER", "PART", "MODE", "JOIN", "PRIVMSG"};

	tokenize(std::string(buffer), '\n', split);
	for (size_t i = 0; i < split.size(); i++)
	{
		bool	commandfound = false;
		for (size_t y = 0; y != 10; y++)
		{
			if (split[i].find(commandList[y]) == 0 && commandfound == false)
			{
				commandfound = true;
				if (!parseCommand(i, y, split))
					return ;
			}
			else if (commandfound == false && y == 9)
				sendToClient(std::string(ERR_UNKNOWNCOMMAND(split[i], _nickname, _username)));
		}
	}
}

bool	client::cap(void)
{
	return true;
}
