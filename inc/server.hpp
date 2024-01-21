/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:43:48 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/21 18:37:17 by cpapot           ###   ########.fr       */
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
# include <map>
# include <vector>
# include <poll.h>

# define MAXCLIENT 64

class serverLogs;

class client;

class channel;

class server
{
private:
	const std::string		_serverName;

	int						_socket;
	struct sockaddr_in		_serverAddrs;
	std::string				_passwd;
	int						_port;
	bool					_status;

	socklen_t				_clientSocketLen;
	sockaddr_in				_clientAddrs;

	std::map<std::string, channel*>	_channelMap;
	std::map<int, client*>			_clientMap;
	std::vector<pollfd>				_pollFds;

	serverLogs						*_logs;

	//server utils
	pollfd					fillPollFd(int socket);
	void					fillSockAddr();
public:
	//server(std::string _passwd, std::string _port);
	server();
	server(int argc, char **argv);
	~server();

	void				deleteChannel(std::string channelName);
	void				assosiateChannel(std::string channelName);
	void				assosiateClientSocket(int clientSocket);
	void				deleteClientSocket(int clientSocket);
	void				parseArg(int argc, char **argv);
	void				launch(void);
	int					acceptClient();
	int					WaitForClient();
	void				sendToAllNetwork(std::string message);

	//command
	bool				ping(int clientSocket, std::vector<std::string> splitLine);
	bool				whoIs(int clientSocket, std::vector<std::string> splitline);

	channel				*getChannel(std::string channel);
	client				*getClient(std::string nickname);
	bool				getStatus(void);
	int					getSocket(void);
	struct sockaddr_in	getAddrs(void);
	std::string			getPasswd(void);
	serverLogs			*getLogs(void);
};

#endif
