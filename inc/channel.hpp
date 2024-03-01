/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:26:23 by cpapot            #+#    #+#             */
/*   Updated: 2024/03/01 12:22:12 by cprojean         ###   ########.fr       */
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
	std::string					_topicSetter;
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
	/*Constructors*/
	channel(std::string	name, int clientSocket);
	~channel();

	/*Setters*/
	void					setIsInviteOnly(bool value);
	void					setIsTopicOperator(bool value);
	void					setIsLocked(bool value, std::string pass);
	void					setIsUserLimit(bool value, unsigned int maxUser);
	void					setTopic(std::string topic, std::string username);
	
	/*Getters*/
	std::map<int, client*>	getClientMap();
	std::string				getChannelName(void);
	std::string				getTopic(void);
	std::string				getTopicSetter(void);
	std::string				getUserStatus(int userSocket);
	
	/*Checkers*/
	bool					isOnChannel(int socket);
	bool					isOnChannelStr(std::string ClientNick);
	bool					isOperator(int clientSocket);
	bool					isTopicOperator(void);
	bool					isInInviteList(std::string ClientNick);

	
	/*Channel commands*/
	int						newClient(client *ClientPtr, std::vector<std::string> splitLine);
	void					disconnectClient(int clientSocket, bool sendPart, std::string message);
	void					sendToAll(std::string message);
	void					sendToAllExept(std::string message, int senderSocket);
	void					makeOperator(int clientSocket);
	void					deleteOperator(int clientSocket);
	void					clearTopic(void);
	void					addToInviteList(std::string ClientNick);
	void					removeFromInviteList(std::string ClientNick);
};

#endif
