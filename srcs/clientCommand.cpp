/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:52:46 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/16 16:00:45 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"

enum {CAP = 0, PASS = 1, NICK = 2, USER = 3};

bool	client::parseCommand(size_t splitIndex, size_t commandIndex, std::vector<std::string> split)
{
	std::vector<std::string>	splitLine;
	tokenize(split[splitIndex], ' ', splitLine);
	if (commandIndex >= 2 && _logged != true)
	{
		sendToClient(std::string(ERR_NOTREGISTERED));
		return false;
	}
	switch (commandIndex)
	{
	case CAP:
		return Cap();
	case PASS:
		return Pass(splitLine);
	case NICK:
		return Nick(splitLine);
	case USER:
		return User(splitLine);
	}
	return false;
}

void	client::findCommand(char buffer[CLIENTBUFFERSIZE])
{
	std::vector<std::string>	split;
	std::string	commandList[4] = {"CAP", "PASS", "NICK", "USER"};

	tokenize(std::string(buffer), '\n', split);
	for (size_t i = 0; i < split.size(); i++)
	{
		bool	commandfound = false;
		for (size_t y = 0; y != 4; y++)
		{
			if (split[i].find(commandList[y]) == 0 && commandfound == false)
			{
				commandfound = true;
				if (!parseCommand(i, y, split))
					return ;
			}
			else if (commandfound == false && y == 3)
			{
				split[i].erase(split[i].size() - 1);
				sendToClient(std::string(ERR_UNKNOWNCOMMAND(split[i])));
			}
		}
	}
}

bool	client::Nick(std::vector<std::string> splitLine)
{
	std::string invalidChar = " &#:\r\n\t\v";

	splitLine[1].erase(splitLine[1].size() - 1);
	for (size_t i = 0; i != splitLine[1].size(); i++)
	{
		for (size_t y = 0; y != invalidChar.size(); y++)
		{
			if (splitLine[1][i] == invalidChar[y])
			{
				sendToClient(std::string(ERR_ERRONEUSNICKNAME));
				return false;
			}
		}
	}
	_nickname = splitLine[1];
	return true;
}

bool	client::User(std::vector<std::string> splitLine)
{
	_username = splitLine[1];
	_hostname = splitLine[2];
	_servername = splitLine[3];
	_realname = splitLine[4].erase(splitLine[4].size() - 1);
	sendToClient("001 " + _nickname + ": Welcome " + _nickname + "\r\n");
	return true;
}

bool	client::Pass(std::vector<std::string> splitLine)
{
	_pass = splitLine[1].erase(splitLine[1].size() - 1);
	if (_pass.compare(_serverPtr->getPasswd()) != 0)
	{
		std::cout << "user pass : \"" << _pass << "\" " << _pass.length() << " pass: \"" << _serverPtr->getPasswd() << "\" " <<  _serverPtr->getPasswd().length() << " value :" << _pass.compare(_serverPtr->getPasswd()) << std::endl;
		sendToClient(std::string(ERR_PASSWDMISMATCH));
		return false;
	}
	sendToClient(std::string("Password correct!!\r\n"));
	_logged = true;
	return true;
}

bool	client::Cap(void)
{
	return true;
}
