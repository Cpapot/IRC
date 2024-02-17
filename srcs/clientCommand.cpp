/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:52:46 by cpapot            #+#    #+#             */
/*   Updated: 2024/02/17 13:33:12 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"

enum {CAP = 0, PASS, PING, QUIT, NICK, USER, PART, MODE, JOIN, PRIVMSG, KICK, INVITE, TOPIC};


					/*Client Commands*/


bool	client::parseCommand(size_t splitIndex, size_t commandIndex, std::vector<std::string> split)
{
	std::vector<std::string>	splitLine;
	tokenize(split[splitIndex], ' ', splitLine);
	if ((commandIndex >= 3 && _logged != true) || (commandIndex >= 6 && _hsDone != true))
	{
		std::cout << "qposioqsio" << std::endl;
		sendToClient(std::string(ERR_NOTREGISTERED(_nickname, _username)));
		return true;
	}
	switch (commandIndex)
	{
	case CAP:
		return cap();
	case PASS:
		return pass(splitLine);
	case NICK:
		return nick(splitLine) || true;
	case USER:
		return user(splitLine) || true;
	case PING:
		return _serverPtr->ping(_clientSocket, splitLine) || true;
	case QUIT:
		return quit(splitLine) || true;
	case PART:
		return part(splitLine) || true;
	case MODE:
		return mode(splitLine) || true;
	case JOIN:
		return join(splitLine) || true;
	case PRIVMSG:
		return privmsg(splitLine) || true;
	case KICK:
		return kick(splitLine) || true;
	case INVITE:
		return invite(splitLine) || true;
	case TOPIC:
		return topic(splitLine) || true;
	}
	return true;
}

bool	client::findCommand(char buffer[CLIENTBUFFERSIZE])
{
	std::vector<std::string>	split;
	std::string	commandList[13] = {"CAP", "PASS", "PING", "QUIT", "NICK", "USER", "PART", "MODE", "JOIN", "PRIVMSG", "KICK", "INVITE", "TOPIC"};

	tokenize(std::string(buffer), '\n', split);
	for (size_t i = 0; i < split.size(); i++)
	{
		bool	commandfound = false;
		for (size_t y = 0; y != 13; y++)
		{
			if (split[i].find(commandList[y]) == 0 && commandfound == false)
			{
				commandfound = true;
				printShit("#d found command %s", commandList[y].c_str());
				if (!parseCommand(i, y, split))
					return false;
			}
			else if (commandfound == false && y == 12)
				sendToClient(std::string(ERR_UNKNOWNCOMMAND(split[i], _nickname, _username)));
		}
	}
	return true;
}

bool	client::cap(void)
{

		printShit("#c CAP LS");
	return true;
}
