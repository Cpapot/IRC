/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABot.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:55:11 by cprojean          #+#    #+#             */
/*   Updated: 2024/01/30 17:16:48 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include <string>

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