/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverLogs.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:22:16 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/20 19:12:07 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGS_HPP
# define LOGS_HPP

# include <fstream>
# include <sstream>
# include <cstdlib>
# include <string>
# include <ctime>


# define LOGS_TABULATION		std::string("					")

class serverLogs
{
private:
	std::ofstream	*_out;

	std::string	getTime(void);
public:
	//void	receive(std::string messageReceive, int source);
	//void	sent(std::string messageSent, int target);


	serverLogs(int port);
	~serverLogs();
};

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
	std::ofstream	out(".log");

	_out = &out;
	*_out << getTime() << "SERVER LAUNCHED ON PORT " << port << std::endl;
}

serverLogs::~serverLogs()
{
	_out->close();
}


#endif
