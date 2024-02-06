/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wall_e.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:51:02 by cprojean          #+#    #+#             */
/*   Updated: 2024/02/06 17:24:15 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "wall_e.hpp"
# include "server.hpp"
# include <stdio.h>
# include <string>
# include "print.hpp"

void	tokenize(std::string const &str, const char delim, std::vector<std::string> &out);

void	wall_e::privmsgBot(std::string mess) const
{
	std::vector<std::string>	splitLine;
	std::string					prompt;
	tokenize(mess, ' ', splitLine);
	if (splitLine[3] != std::string(":") + BOT_PREFIX)
		return ;
	//std::cout << splitLine[4] << std::endl;
	for (size_t i = 4; i != splitLine.size(); i++)
	{
		std::cout << splitLine[i] << std::endl;
		prompt += splitLine[i] + " ";
	}
	/*printShit("#d prompt receive: \"%s\"", prompt);
	std::cout << prompt << std::endl;*/
	sendToServer(PRIVMSG(generateImg(prompt),  splitLine[2]));
}

std::string	wall_e::generateImg(std::string prompt) const
{
	std::cout << prompt << std::endl;
	if (_botStatus == false)
	{
		printShit("#i %s", API_KEY_INVALID);
		return "null\n";
	}
	if (prompt.size() == 0)
	{
		printShit("#i %s", "Prompt can't be empty");
		return "null\n";
	}
	std::string request = CURL_REQUEST(prompt, _apiKey) + " | jq -r '.data[0].url'";
	FILE	*requestAnswer = popen(request.c_str(), "r");
	std::string	result = getStringFromPipe(requestAnswer);
	return result;
}

std::string		wall_e::getStringFromPipe(FILE *pipe) const
{
	std::string	result("");
	char		buffer[FGETS_BOT_BUFFER];

	while (fgets(buffer, FGETS_BOT_BUFFER, pipe) != NULL)
	{
		if (ferror(pipe))
		{
			printShit("#e %s", FGETS_ERROR);
			return "<null>\n";
		}
		result += buffer;
	}
	pclose (pipe);
	return (result);
}

bool	wall_e::setAndCheckApiKey(void)
{
	char	*tmp = std::getenv("DALLE_API_KEY");
	if (tmp == NULL)
	{
		_botStatus = false;
		throw std::invalid_argument("wall_e::" + API_KEY_ERROR);
		return false;
	}
	_apiKey = std::string(tmp);
	std::string checkKeyRequest = "curl -s https://api.openai.com/v1/models -H \"Authorization: Bearer " + _apiKey + "\" | jq '.error'";
	FILE	*requestAnswer = popen(checkKeyRequest.c_str(), "r");
	if (!requestAnswer)
	{
		throw std::invalid_argument("wall_e::" + PIPE_ERROR);
		return false;
	}
	std::string tmpstr = getStringFromPipe(requestAnswer);
	if (tmpstr == "null\n")
	{
		_botStatus = true;
		return true;
	}
	std::cout << tmpstr << std::endl;
	_botStatus = false;
	throw std::invalid_argument("wall_e::" + API_KEY_INVALID);
	return false;
}

wall_e::wall_e(int argc, char **argv)
{
	_username = "Wall-e";
	_nickname = "Wall-e";
	_hostname = "127.0.0.1";
	_servername = "Wall-e";
	_realname = "Wall-e";
	parseArg(argc, argv);
	setAndCheckApiKey();
	connectToServ();
	FD_ZERO(&_readSet);
	FD_SET(_clientSocket, &_readSet);
	_handShakeDone = false;
}

wall_e::~wall_e(void)
{
	close(_clientSocket);
	return ;
}
