/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wall_e.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:51:02 by cprojean          #+#    #+#             */
/*   Updated: 2024/02/07 17:36:26 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "wall_e.hpp"
# include "server.hpp"
# include <stdio.h>
# include <string>
# include "print.hpp"

void	wall_e::privmsgBot(std::vector<std::string> splitLine) const
{
	std::string				prompt;
	printShit("#i %s %s", splitLine[0].c_str(), "is trying to generate an image");
	if (splitLine[3] != std::string(":") + BOT_PREFIX)
		return ;
	for (size_t i = 4; i != splitLine.size(); i++)
	{
		prompt += splitLine[i];
		if (i + 1 != splitLine.size())
			prompt += " ";
	}
	prompt.erase(prompt.size() - 3, prompt.size());
	std::string	message = generateImg(prompt);
	if (message == "null\n")
		message = "An error occured while generating the image, make shire that the prompt is write in english";
	else
	{
		message.erase(message.size() - 1);
		printShit("#i %s \"%s\"", "Image succesfully generated with the prompt:", prompt.c_str());
	}
	sendToServer(PRIVMSG(message, splitLine[2]));
}

std::string	wall_e::generateImg(std::string prompt) const
{
	if (_botStatus == false)
	{
		printShit("#i %s", "The api key you gave is invalid.");
		return "null\n";
	}
	if (prompt.size() == 0)
	{
		printShit("#i %s", "Prompt can't be empty");
		return "null\n";
	}
	std::string request = CURL_REQUEST(prompt, DALL_E_URL, _apiKey) + " | jq -r '.data[0].url'";
	FILE	*requestAnswer = popen(request.c_str(), "r");
	if (requestAnswer == NULL)
		throw std::invalid_argument("wall_e::BrokenPipe");
	std::string	result = getStringFromPipe(requestAnswer);
	return result;
}

std::string		wall_e::getStringFromPipe(FILE *pipe) const
{
	std::string	result;
	char		buffer[FGETS_BOT_BUFFER];

	while (fgets(buffer, FGETS_BOT_BUFFER, pipe) != NULL)
	{
		if (ferror(pipe))
		{
			printShit("#e %s", "fgets() crashed");
			return "null\n";
		}
		result += buffer;
	}
	pclose (pipe);
	//result.erase(result.size() - 1);
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
