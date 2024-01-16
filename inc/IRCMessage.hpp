/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCMessage.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:07:45 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/16 21:44:55 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCMESSAGE_HPP
# define IRCMESSAGE_HPP

# define SPACE		" "
# define END		"\r\n"

# define REPLY(servername, cmd, msg) \
	servername + SPACE + cmd + SPACE + msg + END

# define RPL_WHOISUSER(nick, user, host, real)		std::string("311 :") + nick + SPACE + user + SPACE + host + std::string(" * :") + real + END
# define RPL_UMODEIS(msg)							std::string("221 :") + msg + END

# define ERR_UNKNOWNCOMMAND(cmd)					std::string("421 : \"") + cmd + std::string("\" Unknown command\r\n")
# define ERR_PASSWDMISMATCH							"464 :Password incorrect\r\n"
# define ERR_ALREADYREGISTERED						"462 :You may not reregister\r\n"
# define ERR_NONICKNAMEGIVEN						"431 :No nickname given\r\n"
# define ERR_NOSUCHNICK(nick)						std::string("401 ") + nick + std::string(" : No such nick/channel\r\n")
# define ERR_NEEDMOREPARAMS							"461 :Not enough parameters\r\n"
# define ERR_NOTREGISTERED							"451 :You have not registered\r\n"
# define ERR_ERRONEUSNICKNAME						"432 :Errorneus nickname\r\n"
# define ERR_UMODEUNKNOWNFLAG						"501 :Unknown MODE flag\r\n"
# define ERR_USERSDONTMATCH							"502 :Cant change mode for other users\r\n"
#endif
