/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:42:07 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/21 18:58:05 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "print.hpp"
#include "serverLogs.hpp"

void	client::listenToClient()
{
	char	buffer[CLIENTBUFFERSIZE];

	memset(buffer, 0, sizeof(buffer));
	if (recv(_clientSocket, buffer, sizeof(buffer) - 1, 0) == -1)
		throw	std::invalid_argument("client::CantReceiveMessageFromClient");
	if (buffer[0])
		printShit("#d %s\n", buffer);
	_serverPtr->getLogs()->receive(std::string(buffer), _clientSocket);
	findCommand(buffer);
}

void	client::sendToClient(char* message)
{
	if (send(_clientSocket, message, strlen(message), 0) == -1)
		throw	std::invalid_argument("client::CantSendMessageToClient");
	_serverPtr->getLogs()->sent(message, _clientSocket);
}

void	client::sendToClient(std::string message)
{
	if (send(_clientSocket, message.c_str(), message.length(), 0) == -1)
		throw	std::invalid_argument("client::CantSendMessageToClient");
	_serverPtr->getLogs()->sent(message, _clientSocket);
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
	_modeInvisible = false;
	_modeNotice = false;
	_modeWallops = false;
	_modeOperator = false;
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
	if (DEBUG)
		printShit("#d %s deleted", _nickname.c_str());
}
