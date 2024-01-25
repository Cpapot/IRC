/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCMessage.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:07:45 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/25 17:30:13 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCMESSAGE_HPP
# define IRCMESSAGE_HPP

#define IP			"localhost"

# define AROBASE		"@"
# define SPACE			" "
# define DDOT			":"
# define EXCLAMATION	"!"
# define END			"\r\n"

//UTILS
# define USER_ID(nickname, username)				DDOT + nickname + EXCLAMATION + username + AROBASE + IP + SPACE
# define PREFIX(nick, user, ID)						USER_ID(nick, user) + ID + SPACE + nick + SPACE
# define WELCOME_MSG								"**********************************************\n" + \
													"*                                            *\n" + \
													"*          Welcome to IRC++ Network!         *\n" + \
													"*                                            *\n" + \
													"**********************************************\n" + \
													" \n    Use /join <channel> to join a channel\n \n"

//REPLY
# define RPL_USER(nickname, username, msg)				USER_ID(nickname, username) + std::string("001 ") + nickname + SPACE + DDOT + msg + END
# define RPL_NICK(oldnickname, username, nick)			USER_ID(oldnickname, username) + std::string("NICK ") + nick + END
# define RPL_JOIN(nickname, channel)					DDOT + nickname + std::string(" JOIN ") + channel + END
//# define RPL_WHOISUSER(nick, user, host, real)			std::string("311 :") + nick + SPACE + user + SPACE + host + std::string(" * :") + real + END
//# define RPL_UMODEIS(msg)								std::string("221 :") + msg + END
# define RPL_ENDOFNAMES(nick, user, chan)				PREFIX(nick, user, "464") + chan + ":End of NAMES list" + END
# define RPL_NAMREPLY(nick, user, chan)					PREFIX(nick, user, "353") + std::string("=") + SPACE + chan + std::string(":@") + nick + END
# define RPL_NOTOPIC(nick, user, chan)					PREFIX(nick, user, "331") + chan + ":No topic is set" + END
# define RPL_PING(nick, user, msg)						USER_ID(nick, user) + std::string("PONG") + SPACE + msg + END
# define RPL_PART(nick, user, channel)					USER_ID(nick, user) + std::string("PART") + SPACE + channel + END
# define RPL_QUIT(nick, user, message)					USER_ID(nick, user) + std::string("QUIT") + SPACE + DDOT + message + END
# define RPL_KICK(nick, user, chan, kicknick, message)	USER_ID(nick, user) + std::string("KICK ") + chan + SPACE + kicknick + SPACE + message + END

//ERROR REPLY
# define ERR_UNKNOWNCOMMAND(cmd,nick, user)				PREFIX(nick, user, "421") + std::string("\"") + cmd + std::string("\" Unknown command\r\n")
# define ERR_PASSWDMISMATCH(nick, user)					PREFIX(nick, user, "464") + std::string("Password incorrect\r\n")
# define ERR_ALREADYREGISTERED(nick, user)				PREFIX(nick, user, "432") + std::string("You may not reregister\r\n")
# define ERR_NONICKNAMEGIVEN(nick, user)				PREFIX(nick, user, "431") + std::string("No nickname given\r\n")
# define ERR_NOSUCHNICK(nick, user, nick2)				PREFIX(nick, user, "401") + std::string("\"") + nick2 + std::string("\" No such nick/channel\r\n")
# define ERR_NEEDMOREPARAMS(nick, user)					PREFIX(nick, user, "461") + std::string("Not enough parameters\r\n")
# define ERR_NOTREGISTERED(nick, user)					PREFIX(nick, user, "451") + std::string("You have not registered\r\n")
# define ERR_ERRONEUSNICKNAME(nick, user)				PREFIX(nick, user, "432") + std::string("Errorneus nickname\r\n")
# define ERR_UMODEUNKNOWNFLAG(nick, user)				PREFIX(nick, user, "501") + std::string("Unknown MODE flag\r\n")
# define ERR_NOTONCHANNEL(nick, user, chan)				PREFIX(nick, user, "442") + std::string("\"") + chan + std::string("\" You are not on that channel\r\n")
# define ERR_NOSUCHCHANNEL(nick, user, chan)			PREFIX(nick, user, "403") + std::string("\"") + chan + std::string("\" No such channel\r\n")
# define ERR_USERSDONTMATCH(nick, user)					PREFIX(nick, user, "502") + std::string("Cant change mode for other users") + END
# define ERR_UNKNOWNERROR(nick, user, msg)				PREFIX(nick, user, "400") + msg + END
# define ERR_CHANOPRIVSNEEDED(nick, user, chan)			PREFIX(nick, user, "482") + chan + std::string(" :You're not channel operator") + END
# define ERR_BADCHANNELKEY(nick, user, chan)			PREFIX(nick, user, "475") + chan + std::string(" :Cannot join channel (+k)") + END
# define ERR_CHANNELISFULL(nick, user, chan)			PREFIX(nick, user, "471") + chan + std::string(" :Cannot join channel (+l)") + END
# define ERR_INVITEONLYCHAN(nick, user, chan)			PREFIX(nick, user, "473") + chan + std::string(" :Cannot join channel (+i)") + END
# define ERR_NICKNAMEINUSE(nick)						std::string(": 433 * ") + nick + std::string(" :Nickname is already in use") + END
# define ERR_NOORIGIN(nick, user)						PREFIX(nick, user, "409") + std::string(" :No origin specified") + END
# define ERR_USERNOTINCHANNEL(nick, user, chan)			PREFIX(nick, user, "441") + chan + std::string(" :They aren't on that channel") + END

#endif
