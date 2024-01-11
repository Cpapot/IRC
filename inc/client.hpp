/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 07:02:26 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/11 18:46:34 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <arpa/inet.h>
# include <iostream>
# include <string>
# include <unistd.h>
# include <vector>
# include <cstring>

# define CLIENTBUFFERSIZE	1024

void tokenize(std::string const &str, const char delim, std::vector<std::string> &out);

class client
{
private:
	std::string	_nickname;

	std::string	_username;
	std::string	_hostname;
	std::string	_servername;
	std::string	_realname;

	std::string	_pass;
	int			_clientSocket;
public:
	client(int clientSocket);
	~client();

	void	setClientInfo(char buffer[CLIENTBUFFERSIZE]);
	void	parseConnectionCommand(size_t splitIndex, size_t commandIndex, std::vector<std::string> split);
};

#endif
