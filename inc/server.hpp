/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:43:48 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/11 18:43:05 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <cstring>
# include <unistd.h>
# include <iostream>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <cstdlib>
# include <cerrno>

# define MAXCLIENT 64

class server
{
private:
	int					_socket;
	struct sockaddr_in	_serverAddrs;
	std::string			_passwd;
	uint16_t			_port;
	bool				_status;

	socklen_t			_clientSocketLen;
	sockaddr_in			_clientAddrs;
public:
	//server(std::string _passwd, std::string _port);
	server();
	server(int argc, char **argv);
	~server();

	void	fillSockAddr();
	void	parseArg(int argc, char **argv);
	int		launch(void);
	int		acceptClient();

	bool				getStatus(void);
	int					getSocket(void);
	struct sockaddr_in	getAddrs(void);

	server const	&operator=(const server &src);
};

#endif
