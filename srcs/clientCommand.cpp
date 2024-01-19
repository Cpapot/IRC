/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:52:46 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/19 18:09:42 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"

enum {CAP = 0, PASS, PING, QUIT, NICK, USER, WHOIS, MODE, JOIN, PRIVMSG};

bool	client::parseCommand(size_t splitIndex, size_t commandIndex, std::vector<std::string> split)
{
	std::vector<std::string>	splitLine;
	tokenize(split[splitIndex], ' ', splitLine);
	if (commandIndex >= 3 && _logged != true)
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
	case PING:
		return _serverPtr->ping(_clientSocket, splitLine);
	case QUIT:
		return quit(splitLine);
	case WHOIS:
		return _serverPtr->whoIs(_clientSocket, splitLine);
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
	std::string	commandList[10] = {"CAP", "PASS", "PING", "QUIT","NICK", "USER", "WHOIS", "MODE", "JOIN", "PRIVMSG"};

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
				sendToClient(std::string(ERR_UNKNOWNCOMMAND(split[i])));
		}
	}
}

bool	client::privmsg(std::vector<std::string> splitLine)
{
	std::string message;
	if (splitLine.size() <= 2)
	{
		sendToClient(std::string(ERR_NEEDMOREPARAMS));
		return false;
	}
	if (!_serverPtr->getChannel(splitLine[1]))
	{
		sendToClient(std::string(ERR_NOTONCHANNEL(splitLine[1])));
		return false;
	}
	message = ":" + _nickname + " PRIVMSG " + splitLine[1] + " :";
	splitLine[2].erase(0, 1);
	for (size_t i = 2; i != splitLine.size(); i++)
		message += splitLine[i] + SPACE;
	message += END;
	_serverPtr->getChannel(splitLine[1])->sendToAll(message, _clientSocket);
	new Print(message, MAGENTA, 3);
	return true;
}

bool	client::join(std::vector<std::string> splitLine)
{
	std::string	channelName;
	if (splitLine.size() <= 1)
	{
		sendToClient(std::string(ERR_NEEDMOREPARAMS));
		return false;
	}
	if (splitLine[1][0] == '#')
		channelName = splitLine[1];
	else
	{
		sendToClient(std::string(ERR_NEEDMOREPARAMS));
		return false;
	}
	_serverPtr->assosiateChannel(channelName);
	if (_serverPtr->getChannel(channelName)->newClient(this) == 1)
	{
		sendToClient(std::string(ERR_UNKNOWNERROR("Already log into channel")));
		return false;
	}
	sendToClient(":You are logged into " + channelName + END);
	std::string join = "JOIN : ";
	join += splitLine[1];
	new Print(join, MAGENTA, 3);
	return true;
}

bool	client::mode(std::vector<std::string> splitLine)
{
	bool	mode;

	if (splitLine.size() < 3)
	{
		sendToClient(std::string(ERR_NEEDMOREPARAMS));
		return false;
	}
	if (splitLine[1] != _nickname)
	{
		if (_serverPtr->getClient(splitLine[1]) == NULL)
			sendToClient(std::string(ERR_NOSUCHNICK(splitLine[1])));
		else
			sendToClient(std::string(ERR_USERSDONTMATCH));
		return false;
	}
	if (splitLine[2][0] == '-')
		mode = false;
	else if (splitLine[2][0] == '+')
		mode = true;
	else
	{
		sendToClient(std::string(ERR_UMODEUNKNOWNFLAG));
		return false;
	}
	for (size_t i = 1; i != splitLine[2].size(); i++)
	{
		switch (char(splitLine[2][i]))
		{
			case 'i':
				_modeInvisible = mode;
				break;
			case 'w':
				_modeWallops = mode;
				break;
			case 's':
				_modeNotice = mode;
				break;
			case 'o':
				if (!mode)
					_modeOperator = mode;
				break;
			default:
				sendToClient(std::string(ERR_UMODEUNKNOWNFLAG));
				return false;
		}
	}
	sendToClient(std::string(RPL_UMODEIS(splitLine[1] + SPACE + splitLine[2])));
	return true;
}

bool	client::quit(std::vector<std::string> splitLine)
{
	splitLine[1].erase(0, 1);
	std::cout << _nickname << " is leaving from the server with the message: \"" << splitLine[1] << "\"" << std::endl;
	_serverPtr->deleteClientSocket(_clientSocket);
	std::string quit = "QUIT : ";
	for (unsigned long i = 1; i < splitLine.size(); i++)
		quit += splitLine[i] + SPACE;
	new Print(quit, MAGENTA, 3);
	delete this;
	return true;
}

bool	client::Nick(std::vector<std::string> splitLine)
{
	std::string invalidChar = " &#:\r\n\t\v";

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
	sendToClient("001 " + _nickname + " :Welcome " + _nickname + "\r\n");
	return true;
}

bool	client::Pass(std::vector<std::string> splitLine)
{
	_pass = splitLine[1];
	if (_pass.compare(_serverPtr->getPasswd()) != 0)
	{
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
