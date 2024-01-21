/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:26:23 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/21 21:24:09 by cpapot           ###   ########.fr       */
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
	std::string				_topic;
	unsigned int			_maxUser;

	std::map<int, client*>	_clientMap;
	std::vector<int>		_operatorList;

	//channel option set by operator
	bool					_isInviteOnly;
	bool					_isTopicOperator;
	bool					_isLocked;
	bool					_isUserLimit;
public:
	channel(std::string	name, int clientSocket);
	~channel();

	int		newClient(client *ClientPtr, std::vector<std::string> splitLine);
	void	disconnectClient(int clientSocket);

	void	sendToAll(std::string message);
	void	sendToAllExept(std::string message, int senderSocket);

	bool	isOperator(int clientSocket);
	void	makeOperator(int clientSocket);
	void	deleteOperator(int clientSocket);

	std::string	getChannelName(void);
};

#endif
