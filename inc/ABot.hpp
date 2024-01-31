/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABot.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:55:11 by cprojean          #+#    #+#             */
/*   Updated: 2024/01/31 13:31:09 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABOT_HPP
# define ABOT_HPP

# include <string>

class server;

class ABot
{
	protected :
			std::string			_nickname;

			std::string			_username;
			std::string			_hostname;
			std::string			_servername;
			std::string			_realname;

			server				*_serverPtr;

			std::string			_pass;
			std::string			_port;
			int					_clientSocket;
			bool				_logged;
			bool				_modeInvisible;
			bool				_modeNotice;
			bool				_modeWallops;
			bool				_modeOperator;

	public :
			ABot(void);
			ABot(int clientSocket, server *serverPtr, char **argv);
			virtual ~ABot( void );
			virtual bool routine() const = 0;
};

#endif
