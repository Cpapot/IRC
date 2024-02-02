/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABot.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:55:11 by cprojean          #+#    #+#             */
/*   Updated: 2024/02/02 12:06:12 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABOT_HPP
# define ABOT_HPP

# include <string>
# include <sys/types.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <iostream>
# include <unistd.h>
# include <arpa/inet.h>

# define SERVERMESSAGEBUFFER				1024

# define END								"\r\n"
# define SPACE								" "

# define HS_CAP								std::string("CAP LS") + END
# define HS_PASS(pass)						std::string("PASS ") + pass + END
# define HS_NICK(nick)						std::string("NICK ") + nick + END
# define HS_USER(user, real, host, serv)	std::string("USER ") + user + SPACE + host + SPACE + serv + std::string(" :") + real + END

class ABot
{
	protected :
		std::string			_nickname;

		std::string			_username;
		std::string			_hostname;
		std::string			_servername;
		std::string			_realname;

		int					_clientSocket;

		sockaddr_in			_serverAddress;
		int					_serverSocket;
		std::string			_serverPass;

		void	parseArg(int argc, char **argv);
		void	connectToServ();
		void	fillSockAddr();
	public :
		ABot(void);

		virtual ~ABot( void );
		//virtual bool routine() const = 0;
		bool			sendToServer(std::string message);
		std::string		listenToServer();
		void	sendFirstHandShake();
};

#endif
