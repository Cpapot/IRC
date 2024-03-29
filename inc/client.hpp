/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 07:02:26 by cpapot            #+#    #+#             */
/*   Updated: 2024/02/13 15:09:56 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <arpa/inet.h>
# include <iostream>
# include <string>
# include <unistd.h>
# include <vector>
# include <cstring>
# include "server.hpp"
# include "print.hpp"

# define CLIENTBUFFERSIZE	1024

void tokenize(std::string const &str, const char delim, std::vector<std::string> &out);

class server;

class client
{
private:
	std::string					_nickname;

	std::string					_username;
	std::string					_hostname;
	std::string					_servername;
	std::string					_realname;

	std::string					_pass;
	int							_clientSocket;
	bool						_logged;

	std::vector<std::string>	_loggedChannel;

	//MODE
	bool						_modeInvisible;
	bool						_modeNotice;
	bool						_modeWallops;
	bool						_modeOperator;

	server						*_serverPtr;

	//utils
	bool						_userAnswerSent;
	bool						_badNick;

	/*Private functions*/
	bool	modeUser(std::vector<std::string> splitLine);
	bool	modeChannel(std::vector<std::string> splitLine);
	bool	privateMessage(std::string message, std::vector<std::string> splitLine, int i);
	bool	sendFile(std::string message, std::vector<std::string> splitLine, int i);
	void	joinInfo(std::string channel);

public:
	/*Constructors*/
	client(int _clientSocket, server *serverPtr);
	~client();

	/*Utils*/
	void	sendToClient(std::string message);
	void	sendToClient(char *message);
	bool	listenToClient();
	bool	parseCommand(size_t splitIndex, size_t commandIndex, std::vector<std::string> split);

	/*Commands*/
	bool	findCommand(char buffer[CLIENTBUFFERSIZE]);
	bool	nick(std::vector<std::string> splitLine);
	bool	user(std::vector<std::string> splitLine);
	bool	pass(std::vector<std::string> splitLine);
	bool	cap(void);
	bool	quit(std::vector<std::string> splitLine);
	bool	mode(std::vector<std::string> splitLine);
	bool	join(std::vector<std::string> splitLine);
	bool	privmsg(std::vector<std::string> splitLine);
	bool	part(std::vector<std::string> splitLine);
	bool	kick(std::vector<std::string> splitLine);
	bool	invite(std::vector<std::string> splitLine);
	bool	topic(std::vector<std::string> splitLine);

	/*Getters*/
	std::string	getUsername(void);
	std::string	getNickname(void);
	std::string	getHostname(void);
	std::string	getRealname(void);
	std::string	getPass(void);
	int			getSocket(void);

	friend std::ostream& operator<<(std::ostream& os, const client& dt);
};

#endif
