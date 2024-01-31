/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:43:48 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/30 11:11:39 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Irc.hpp"

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
	void				assosiateChannel(std::string channelName, int clientSocket);
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
