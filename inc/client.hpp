/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 07:02:26 by cpapot            #+#    #+#             */
/*   Updated: 2023/12/03 07:35:28 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "server.hpp"

//le client depend du server
class client: public server
{
private:
	socklen_t	_clientSocketLen;
	int			_clientSocket;
	sockaddr_in	_clientAddrs;
public:
	client(/* args */);
	~client();

	int		acceptClient(void);

	//test
	void	printmsg();
};

void	client::printmsg()
{
	char	buffer[1024];

	memset(buffer, 0, sizeof(buffer));
	if (recv(_clientSocket, buffer, sizeof(buffer) - 1, 0) == -1)
		std::cout << "Error" << std::endl;
	else
		std::cout << "message : \"" << buffer << "\"" << std::endl;
}

int	client::acceptClient()
{
	std::cout << "Waiting for client" << std::endl;
	_clientSocket = accept(_socket, (struct sockaddr*)&_clientAddrs, &_clientSocketLen);
	if (_clientSocket == -1)
	{
		std::cout << "client can't connect" << std::endl;
		return 0;
	}
	std::cout << "Connexion accepted" << std::endl;
	return 1;
}
client::client(/* args */)
{
	_clientSocketLen = sizeof(_clientAddrs);
	this->acceptClient();
	this->printmsg();
}

client::~client()
{
}

#endif
