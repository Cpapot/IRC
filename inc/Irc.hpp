/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:07:16 by cprojean          #+#    #+#             */
/*   Updated: 2024/01/30 13:51:59 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# include <fstream>
# include <sstream>
# include <cstdlib>
# include <ctime>
# include <cstring>
# include <cstdarg>
# include <string>
# include <iostream>

# include <arpa/inet.h>
# include <unistd.h>
# include <poll.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>

# include <cerrno>
# include <map>
# include <vector>

# include "server.hpp"
# include "client.hpp"
# include "print.hpp"
# include "serverLogs.hpp"
# include "channel.hpp"
# include "IRCMessage.hpp"
# include "ABot.hpp"
# include "Wall_e.hpp"

#endif