/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:43:48 by cpapot            #+#    #+#             */
/*   Updated: 2023/12/01 10:50:05 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

class server
{
private:
	std::string		_passwd;
	std::string		_port;
public:
	server(std::string _passwd, std::string _port);
	server();
	~server();
};

server::server(/* args */)
{
}

server::~server()
{
}
