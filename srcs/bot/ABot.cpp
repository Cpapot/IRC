/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABot.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:06:26 by cprojean          #+#    #+#             */
/*   Updated: 2024/02/13 16:22:26 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABot.hpp"
#include "print.hpp"
#include <cstdlib>
#include <sys/time.h>
#include <cstring>

void	tokenize(std::string const &str, const char delim, std::vector<std::string> &out);


				/*Constructors*/


ABot::ABot(void)
{
	_username = "Random Bot";
	_nickname = "Random Bot";
	_hostname = "Random Bot";
	_servername = "";
	_realname = "";
}

ABot::~ABot(void)
{
	close(_clientSocket);
	return ;
}


					/*ABot utils*/


void	ABot::fillSockAddr()
{
	sockaddr_in server;

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(_serverSocket);
	_serverAddress = server;
}

void	ABot::parseArg(int argc, char **argv)
{
	if (argc != 3)
		throw std::invalid_argument("ABot::InvalidArgument");
	_serverSocket = std::atol(argv[1]);
	if (_serverSocket <= 0 || _serverSocket >= 65536)
		throw std::invalid_argument("ABot::invalidPort");
	_serverPass = std::string(argv[2]);
}

bool	ABot::sendToServer(std::string message) const
{
	if (send(_clientSocket, message.c_str(), message.length(), 0) == -1)
		return false;
	printShit("#d %s", "Message sent to server");
	return true;
}

void	ABot::connectToServ()
{
	fillSockAddr();
	_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_clientSocket == -1)
		throw std::invalid_argument("ABot::FailedToOpenSocket");
	_isOpen = true;
	if (connect(_clientSocket, (struct sockaddr*)&_serverAddress, sizeof(_serverAddress)) == -1)
		throw std::invalid_argument("ABot::FailedToConnectOnServer");
	printShit("#i %s", "Successfully connected to server");
}

void			ABot::waitForServer(void)
{
	bool	cpSent = false;
	struct	timeval timeout;
	while (true)
	{
		FD_ZERO(&_readSet);
		FD_SET(_clientSocket, &_readSet);
		timeout.tv_sec = 0;
		timeout.tv_usec = 100;

		if (_handShakeDone == false && cpSent == false)
		{
			sendToServer(HS_CAP);
			sendToServer(HS_PASS(_serverPass));
			cpSent = true;
		}
		int selectRes = select(_clientSocket + 1, &_readSet, NULL, NULL, &timeout);
		if (selectRes == -1)
			throw std::invalid_argument("ABot::failedToSelectFd");
		else if (selectRes > 0)
		{
			if (FD_ISSET(_clientSocket, &_readSet))
			{
				if (!parseServerCommand(listenToServer()))
					return ;
			}
		}
		usleep(10000);
	}
}

bool	ABot::parseServerCommand(std::string message)
{
	if (!message[0])
		return false;
	message.erase(message.size() - 2);
	std::vector<std::string>	splitLine;
	tokenize(message, ' ', splitLine);
	if (_handShakeDone == false)
	{
		if (splitLine.size() == 1)
		{
			_handShakeDone = true;
			sendToServer(HS_NICK(_nickname));
			sendToServer(HS_USER(_username, _realname, _hostname, _servername));
			printShit("#i %s", "Successfully logged to server");
		}
		else
			throw std::invalid_argument("ABot::BadPass");
	}
	else
	{
		if (splitLine[1] == "433")
		{
			disconnectBot("Bot Disconnected due to an error");
			throw std::invalid_argument("ABot::BotIsAlreadyLoggedOrHisNickIsTaken");
			return true;
		}
		if (splitLine[1] == "JOIN" && !isInChannelList(splitLine[2]) && splitLine[0] != ":" + _nickname)
		{
			printShit("#i %s %s", splitLine[2].c_str(), "joined");
			sendToServer(JOIN(splitLine[2]));
			_channelList.push_back(splitLine[2]);
			return true;
		}
		if (splitLine[1] == "PRIVMSG" && isInChannelList(splitLine[2]))
		{
			privmsgBot(splitLine);
			return true;
		}
		else if (splitLine[1] == "PRIVMSG" && !isInChannelList(splitLine[2]))
			printShit("#e %s", "Message from a chanel in which the bot is not");
	}
	return true;
}

void	ABot::disconnectBot(std::string message)
{
	if (_isOpen && _handShakeDone)
	{
		sendToServer(std::string("QUIT :") + message + std::string("\r\n"));
	}
}

bool	ABot::isInChannelList(std::string channel)
{
	for (size_t index = 0; index != _channelList.size(); index++)
	{
		if (_channelList[index] == channel)
			return true;
	}
	return false;
}

std::string		ABot::listenToServer()
{
	char	buffer[SERVERMESSAGEBUFFER];

	memset(buffer, 0, sizeof(buffer));
	if (recv(_clientSocket, buffer, sizeof(buffer) - 1, 0) == -1)
		throw std::invalid_argument("ABot::CantReceiveMessageFromServer");
	if (buffer[0])
		printShit("#d %s\n", buffer);
	std::string result(buffer);
	return (result);
}
