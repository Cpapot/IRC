/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:00:24 by cpapot            #+#    #+#             */
/*   Updated: 2024/03/06 16:04:09 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"

bool	IsChannel(std::string str);

bool	client::modeChannel(std::vector<std::string> splitLine)
{
	bool	mode;

	if (_serverPtr->getChannel(splitLine[1]) == NULL)
	{
		sendToClient(ERR_NOSUCHCHANNEL(_nickname, _username, splitLine[1]));
		return false;
	}
	if (!_serverPtr->getChannel(splitLine[1])->isOperator(_clientSocket))
	{
		sendToClient(ERR_CHANOPRIVSNEEDED(_nickname, _username, splitLine[1]));
		return false;
	}
	if (splitLine[2][0] == '-')
		mode = false;
	else if (splitLine[2][0] == '+')
		mode = true;
	else
	{
		sendToClient(std::string(ERR_UMODEUNKNOWNFLAG(_nickname, _username, splitLine[1])));
		return false;
	}
	for (size_t i = 1; i != splitLine[2].size(); i++)
	{
		switch (char(splitLine[2][i]))
		{
			case 'i':
				_serverPtr->getChannel(splitLine[1])->setIsInviteOnly(mode);
				printShit("#c %s : switched the channel to mode Invite Only", splitLine[1].c_str());
				break;

			case 't':
				_serverPtr->getChannel(splitLine[1])->setIsTopicOperator(mode);
				printShit("#c %s : set a topic", splitLine[1].c_str());
				break;

			case 'k':
				if (mode == false)
					_serverPtr->getChannel(splitLine[1])->setIsLocked(false, "");
				else
				{
					if (splitLine.size() >= 4)
						_serverPtr->getChannel(splitLine[1])->setIsLocked(true, splitLine[3]);
					else
					{
						sendToClient(std::string(ERR_NEEDMOREPARAMS(_nickname, _username)));
						return false;
					}
				}
				printShit("#c %s : mode Restricted triggered", splitLine[1].c_str());
				break;

			case 'l':
				if (mode == false)
					_serverPtr->getChannel(splitLine[1])->setIsUserLimit(false, 0);
				else
				{
					if (splitLine.size() >= 4)
					{
						if (atoi(splitLine[3].c_str()) <= 0)
						{
							sendToClient(ERR_UNKNOWNERROR(_nickname, _username, "Invalid User Limit"));
							return false;
						}
						else
							_serverPtr->getChannel(splitLine[1])->setIsUserLimit(true, atoi(splitLine[3].c_str()));
					}
					else
					{
						sendToClient(std::string(ERR_NEEDMOREPARAMS(_nickname, _username)));
						return false;
					}
				}
				printShit("#c %s : mode Limit triggered", splitLine[1].c_str());
				break;

			case 'o':
				if (splitLine.size() <= 3)
				{
					sendToClient(ERR_NEEDMOREPARAMS(_nickname, _username));
					return false;
				}
				if (!_serverPtr->getChannel(splitLine[1])->isOnChannelStr(splitLine[3]))
				{
					sendToClient(ERR_NOSUCHNICK(_nickname, _username, splitLine[3]));
					return false;
				}
				if (mode)
					_serverPtr->getChannel(splitLine[1])->makeOperator(_serverPtr->getClient(splitLine[3])->getSocket());
				else
					_serverPtr->getChannel(splitLine[1])->deleteOperator(_serverPtr->getClient(splitLine[3])->getSocket());
				break;

			default:
				sendToClient(std::string(ERR_UMODEUNKNOWNFLAG(_nickname, _username, splitLine[1])));
				return false;
		}
	}
	_serverPtr->getChannel(splitLine[1])->sendToAll(RPL_CHANMODE(_nickname, _username, splitLine[1], splitLine[2]));
	return true;
}


bool	client::modeUser(std::vector<std::string> splitLine)
{
	bool	mode;

	if (splitLine[1] != _nickname)
	{
		if (_serverPtr->getClient(splitLine[1]) == NULL)
			sendToClient(std::string(ERR_NOSUCHNICK(_nickname, _username, splitLine[1])));
		else
			sendToClient(std::string(ERR_USERSDONTMATCH(_nickname, _username)));
		return false;
	}
	if (splitLine[2][0] == '-')
		mode = false;
	else if (splitLine[2][0] == '+')
		mode = true;
	else
	{
		sendToClient(std::string(ERR_UMODEUNKNOWNFLAG(_nickname, _username, "")));
		return false;
	}
	for (size_t i = 1; i != splitLine[2].size(); i++)
	{
		switch (char(splitLine[2][i]))
		{
			case 'i':
				_modeInvisible = mode;
				break;
			case 'w':
				_modeWallops = mode;
				break;
			case 's':
				_modeNotice = mode;
				break;
			case 'o':
				if (!mode)
					_modeOperator = mode;
				break;
			default:

				sendToClient(std::string(ERR_UMODEUNKNOWNFLAG(_nickname, _username, "")));
				return false;
		}
	}
	// sendToClient(std::string(RPL_UMODEIS(splitLine[1] + SPACE + splitLine[2])));
	return true;
}

bool	client::mode(std::vector<std::string> splitLine)
{
	if (splitLine.size() < 3)
	{
		sendToClient(std::string(ERR_NEEDMOREPARAMS(_nickname, _username)));
		return false;
	}
	if (!IsChannel(splitLine[1]))
		return modeUser(splitLine);
	else
		return modeChannel(splitLine);
}
