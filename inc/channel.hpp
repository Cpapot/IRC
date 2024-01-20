/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:26:23 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/19 17:49:40 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <string>
#include "client.hpp"

class channel
{
private:
	std::string				_channelName;
	std::string				_passwd;

	std::map<int, client*>	_clientMap;
public:
	channel(std::string	name);
	~channel();

	int		newClient(client *ClientPtr);
	void	disconnectClient(int clientSocket);

	void	sendToAll(std::string message);
	void	sendToAllExept(std::string message, int senderSocket);

	std::string	getChannelName(void);
};

#endif
