/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:26:23 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/31 13:29:16 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <map>
# include "client.hpp"

class channel
{
private:
	std::string					_channelName;

	std::string					_passwd;
	std::string					_topic;
	unsigned int				_maxUser;

	std::map<int, client*>		_clientMap;
	std::vector<int>			_operatorList;
	std::vector<std::string>	_inviteList;

	//channel option set by operator
	bool						_isInviteOnly;
	bool						_isTopicOperator;
	bool						_isLocked;
	bool						_isUserLimit;
public:
	channel(std::string	name, int clientSocket);
	~channel();

	int						newClient(client *ClientPtr, std::vector<std::string> splitLine);
	bool					isOnChannel(int socket);
	bool					isOnChannelStr(std::string ClientNick);
	void					disconnectClient(int clientSocket, bool sendPart);

	void					sendToAll(std::string message);
	void					sendToAllExept(std::string message, int senderSocket);

	bool					isOperator(int clientSocket);
	void					makeOperator(int clientSocket);
	void					deleteOperator(int clientSocket);

	std::string				getChannelName(void);
	void					setIsInviteOnly(bool value);
	void					setIsTopicOperator(bool value);
	void					setIsLocked(bool value, std::string pass);
	void					setIsUserLimit(bool value, unsigned int maxUser);

	void					setTopic(std::string topic);
	void					clearTopic(void);
	std::string				getTopic(void);
	bool					isTopicOperator(void);

	void					addToInviteList(std::string ClientNick);
	void					removeFromInviteList(std::string ClientNick);
	bool					isInInviteList(std::string ClientNick);

};

#endif
