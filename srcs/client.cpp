/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:42:07 by cpapot            #+#    #+#             */
/*   Updated: 2024/02/17 14:37:05 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "print.hpp"
#include "serverLogs.hpp"


					/*Constructors*/


client::client(int clientSocket, server *serverPtr)
{
	_logged = false;
	_modeInvisible = false;
	_modeNotice = false;
	_modeWallops = false;
	_modeOperator = false;
	_userAnswerSent = false;
	_badNick = false;
	_hsDone = false;
	_messageBuffer = "";
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
	printShit("#d %s deleted", _nickname.c_str());
}


					/*Getters*/


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

					/*Client utils*/


bool	client::listenToClient()
{
	char			buffer[CLIENTBUFFERSIZE];
	std::string		message;

	memset(buffer, 0, sizeof(buffer));
	if (recv(_clientSocket, buffer, sizeof(buffer) - 1, 0) == -1)
		throw	std::invalid_argument("client::CantReceiveMessageFromClient");
	message = buffer;
	if (message[0] && message[message.size() - 1] != '\n')
	{
		_messageBuffer += message;
		return true;
	}
	else if (message[0])
	{
		message = _messageBuffer + message;
		_messageBuffer = "";
	}
	if (message[0] && message[message.size() - 2] != '\r' && message[message.size() - 1] == '\n')
		message.insert((int)message.length() - 1, 1, '\r');
	if (message[0])
	{
		printShit("#d %s\n", message);
		_serverPtr->getLogs()->receive(message, _clientSocket);
		return findCommand(message);
	}
	else
		return false;
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
