/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCMessage.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:07:45 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/16 15:49:47 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCMESSAGE_HPP
# define IRCMESSAGE_HPP

# define SPACE		" "
# define END		"\r\n"


# define REPLY(servername, cmd, msg) \
	servername + SPACE + cmd + SPACE + msg + END

# define ERR_UNKNOWNCOMMAND(cmd)	std::string("421 : \"") + cmd + std::string("\" Unknown command\r\n")
# define ERR_PASSWDMISMATCH			"464 : Password incorrect\r\n"
# define ERR_ALREADYREGISTERED		"462 : You may not reregister\r\n"
# define ERR_NEEDMOREPARAMS			"461 : Not enough parameters\r\n"
# define ERR_NOTREGISTERED			"451 : You have not registered\r\n"
# define ERR_ERRONEUSNICKNAME		"432 : Errorneus nickname\r\n"

#endif
