/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABot.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:06:26 by cprojean          #+#    #+#             */
/*   Updated: 2024/02/02 12:09:53 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABot.hpp"
#include "print.hpp"
#include <cstdlib>
#include <cstring>

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

bool	ABot::sendToServer(std::string message)
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
	if (connect(_clientSocket, (struct sockaddr*)&_serverAddress, sizeof(_serverAddress)) == -1)
		throw std::invalid_argument("ABot::FailedToConnectOnServer");
	printShit("#i %s", "Succeffuly connected to server");
}

std::string		ABot::listenToServer()
{
	char	buffer[SERVERMESSAGEBUFFER];

	memset(buffer, 0, sizeof(buffer));
	if (recv(_serverSocket, buffer, sizeof(buffer) - 1, 0) == -1)
		throw std::invalid_argument("ABot::CantReceiveMessageFromServer");
	if (buffer[0])
		printShit("#d %s\n", buffer);
	std::string result(buffer);
	return (result);
}

void	ABot::sendFirstHandShake()
{
	sendToServer(HS_CAP);
	sendToServer(HS_PASS(_serverPass));
	sendToServer(HS_NICK(_nickname));
	sendToServer(HS_USER(_username, _realname, _hostname, _servername));
}
