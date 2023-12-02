/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:43:48 by cpapot            #+#    #+#             */
/*   Updated: 2023/12/02 15:35:23 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>

class server
{
private:
	std::string		_passwd;
	std::string		_port;
	int				_socket;
	struct sockaddr	_addrs;
public:
	//server(std::string _passwd, std::string _port);
	server();
	~server();

	void	fillSockAddr();
	int		launch(void);
};

int		server::launch(void)
{
	//crée un socket (comme un fd)
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1)
	{
		std::cout << "Failed to open socket." << std::endl;
		return 0;
	}
	//affecte le socket a un nom
	if(bind(_socket, ) == -1)
	{
		std::cout << "Failed to bind socket." << std::endl;
		return 0;
	}
}

server::server(/* args */)
{
	_port = "6667";
	_passwd = "1234";
	this->launch();
}

server::~server()
{
}
