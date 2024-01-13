/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:42:07 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/13 17:43:01 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

enum {CAP = 0, USER = 1, NICK = 2, PASS = 3};

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

bool	client::parseConnectionCommand(size_t splitIndex, size_t commandIndex, std::vector<std::string> split)
{
	std::vector<std::string>	splitLine;
	tokenize(split[splitIndex], ' ', splitLine);
	switch (commandIndex)
	{
	case CAP:
		return hsCap();
		break;
	case USER:
		return hsUser(splitLine);
		break;
	case NICK:
		return hsNick(splitLine);
		break;
	case PASS:
		return hsPass(splitLine);
		break;
	default:
		return false;
	}
}

void	client::setClientInfo(char buffer[CLIENTBUFFERSIZE])
{
	std::string					rawSTR(buffer);
	std::vector<std::string>	split;
	std::string	commandList[4] = {"CAP", "USER", "NICK", "PASS"};

	tokenize(rawSTR, '\n', split);
	for (size_t i = 0; i < split.size(); i++)
	{
		bool	commandfound = false;
		for (size_t y = 0; y != 4; y++)
		{
			if (split[i].find(commandList[y]) == 0 && commandfound == false)
			{
				commandfound = true;
				if (!parseConnectionCommand(i, y, split))
					return ;
			}
			else if (commandfound == false && y == 3)
			{
				std::cout << i << "  " << y << std::endl;
				throw std::invalid_argument("client::InvalidConnectionCommand");
			}
		}
	}
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

client::client(int clientSocket)
{
	_pass = "";
	_username = "";
	_nickname = "";
	_hostname = "";
	_servername = "";
	_realname = "";
	char	buffer[CLIENTBUFFERSIZE];
	_clientSocket = clientSocket;
	memset(buffer, 0, sizeof(buffer));
	if (recv(_clientSocket, buffer, sizeof(buffer) - 1, 0) == -1)
		std::cout << "Error" << std::endl;
	else
	{
		std::cout << "\"" << buffer << "\"" << std::endl;
		setClientInfo(buffer);
	}
}

client::~client()
{
	close(_clientSocket);
}
