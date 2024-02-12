/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverLogs.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:41:44 by cpapot            #+#    #+#             */
/*   Updated: 2024/02/12 18:51:00 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serverLogs.hpp"


					/*Server Log Utils*/


void	serverLogs::sent(std::string messageSent, int target)
{
	messageSent.erase(messageSent.size() - 2, messageSent.size());
	_out << getTime() << "sent: \"" << messageSent << "\" to: " << target << std::endl;
}

void	serverLogs::receive(std::string messageReceive, int source)
{
	std::string		newline;
	std::string		tmp;

	messageReceive.erase(messageReceive.size() - 2, messageReceive.size());
	for (size_t pos = messageReceive.find('\n'); pos != std::string::npos; pos = messageReceive.find('\n'))
	{
		tmp = messageReceive;
		messageReceive.erase(0, 1 + pos);
		newline += tmp.substr(0, pos - 1) + std::string("		");
	}
	newline += messageReceive;
	_out << getTime() << "receive: \"" << newline << "\" from: " << source << std::endl;
}

std::string	serverLogs::getTime(void)
{
	std::time_t				t = std::time(0);
	std::tm					*now = std::localtime(&t);
	std::stringstream		resultStream;

	resultStream << "[" << now->tm_hour << ":" << now->tm_min << "]" << LOGS_TABULATION;
	return resultStream.str();
}

serverLogs::serverLogs(int port)
{
	_out.open(".log", std::ofstream::out);
	_out << getTime() << "SERVER LAUNCHED ON PORT " << port << std::endl;
}

serverLogs::~serverLogs()
{
	_out.close();
}
