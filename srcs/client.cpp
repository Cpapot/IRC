/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:42:07 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/15 12:53:26 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"

enum {CAP = 0, PASS = 1, NICK = 2, USER = 3};

void	client::listenToClient()
{
	char	buffer[CLIENTBUFFERSIZE];

	memset(buffer, 0, sizeof(buffer));
	if (recv(_clientSocket, buffer, sizeof(buffer) - 1, 0) == -1)
		throw	std::invalid_argument("client::CantReceiveMessageFromClient");
	std::cout << buffer << std::endl;
	findCommand(buffer);
}

void	client::sendToClient(char* message)
{
	if (send(_clientSocket, message, strlen(message), 0) == -1)
		throw	std::invalid_argument("client::CantSendMessageToClient");
}

void	client::sendToClient(std::string message)
{
	if (send(_clientSocket, message.c_str(), message.length(), 0) == -1)
		throw	std::invalid_argument("client::CantSendMessageToClient");
	else
		std::cout << "\033[1;32m message sent : \"" << message << "\"\033[0m" << std::endl;
}

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
		break;
	case PASS:
		return Pass(splitLine);
		break;
	case NICK:
		return Nick(splitLine);
		break;
	case USER:
		return User(splitLine);
		break;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const client& dt)
{
	os << "nickname : " << dt._nickname << std::endl;
	os << "username : " << dt._username << std::endl;
	os << "hostname : " << dt._hostname << std::endl;
	os << "servername : " << dt._servername << std::endl;
	os << "realname : " << dt._realname << std::endl;
	os << "pass : " << dt._pass << std::endl;
	return os;
}

std::string	client::getUsername(void)
{
	return (_username);
}

std::string	client::getNickname(void)
{
	return (_nickname);
}

std::string	client::getHostname(void)
{
	return (_hostname);
}

std::string	client::getRealname(void)
{
	return (_realname);
}

std::string	client::getPass(void)
{
	return (_pass);
}

int	client::getSocket(void)
{
	return (_clientSocket);
}

client::client(int clientSocket, server *serverPtr)
{
	_logged = false;
	_pass = "";
	_username = "";
	_nickname = "";
	_hostname = "";
	_servername = "";
	_realname = "";
	_clientSocket = clientSocket;
	_serverPtr = serverPtr;
}

client::~client()
{
	close(_clientSocket);
}
