/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABot.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:55:11 by cprojean          #+#    #+#             */
/*   Updated: 2024/02/12 15:14:43 by cpapot           ###   ########.fr       */
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
# include <poll.h>
# include <vector>

# define SERVERMESSAGEBUFFER				1024

# define END								"\r\n"
# define SPACE								" "

# define HS_CAP								std::string("CAP LS") + END
# define HS_PASS(pass)						std::string("PASS ") + pass + END
# define HS_NICK(nick)						std::string("NICK ") + nick + END
# define HS_USER(user, real, host, serv)	std::string("USER ") + user + SPACE + host + SPACE + serv + std::string(" :") + real + END
# define JOIN(channel)						std::string("JOIN ") + channel
# define PRIVMSG(message, channel)			std::string("PRIVMSG ") + channel + std::string(" :") + message + END

class ABot
{
	protected :
		std::string					_nickname;

		std::string					_username;
		std::string					_hostname;
		std::string					_servername;
		std::string					_realname;

		int							_clientSocket;

		sockaddr_in					_serverAddress;
		int							_serverSocket;
		std::string					_serverPass;

		fd_set						_readSet;

		bool						_handShakeDone;
		bool						_isOpen;

		std::vector<std::string>	_channelList;

		void						parseArg(int argc, char **argv);
		void						connectToServ();
		void						fillSockAddr();
	public :
		ABot(void);

		virtual			~ABot( void );

		virtual	void	privmsgBot(std::vector<std::string> splitLine) const = 0;

		void			waitForServer(void);
		bool			sendToServer(std::string message) const;
		std::string		listenToServer();
		bool			parseServerCommand(std::string message);

		void			disconnectBot(std::string message);
		bool			isInChannelList(std::string channel);
};

#endif
