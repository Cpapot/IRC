/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:42:07 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/11 18:50:00 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

void	client::parseConnectionCommand(size_t splitIndex, size_t commandIndex, std::vector<std::string> split)
{

}

void	client::setClientInfo(char buffer[CLIENTBUFFERSIZE])
{
	std::string					rawSTR(buffer);
	std::vector<std::string>	split;
	std::string	commandList[4] = {"CAP LS", "USER", "NICK", "PASS"};

	tokenize(rawSTR, '\n', split);
	for (size_t i = 0; i < split.size(); i++)
	{
		for (size_t y = 0; y != 4; y++)
		{
			bool	commandfound = false;
			if (split[i].find(commandList[y]) == 0 && commandfound == false)
			{
				commandfound = true;
				//parseConnectionCommand(i, y, split);
			}
			else if (commandfound == false && y == 3)
				throw std::invalid_argument("client::InvalidConnectionCommand");
		}
	}
}


client::client(int clientSocket)
{
	char	buffer[CLIENTBUFFERSIZE];
	_clientSocket = clientSocket;
	memset(buffer, 0, sizeof(buffer));
	if (recv(_clientSocket, buffer, sizeof(buffer) - 1, 0) == -1)
		std::cout << "Error" << std::endl;
	else
		setClientInfo(buffer);
}

client::~client()
{
	close(_clientSocket);
}
