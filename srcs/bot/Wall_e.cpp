/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wall_e.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:51:02 by cprojean          #+#    #+#             */
/*   Updated: 2024/02/17 15:14:32 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "wall_e.hpp"
# include "server.hpp"
# include <stdio.h>
# include <string>
# include "print.hpp"


					/*Constructors*/


wall_e::wall_e(int argc, char **argv)
{
	_username = "Wall-e";
	_nickname = "Wall-e";
	_hostname = "127.0.0.1";
	_servername = "Wall-e";
	_realname = "Wall-e";
	_isOpen = false;
	_handShakeDone = false;
	parseArg(argc, argv);
	setAndCheckApiKey();
	connectToServ();
	FD_ZERO(&_readSet);
	FD_SET(_clientSocket, &_readSet);
}

wall_e::~wall_e(void)
{
	if (_isOpen)
		close(_clientSocket);
	return ;
}


					/*Wall-e utils*/


std::string	wall_e::cleanPrompt(std::vector<std::string> splitLine) const
{
	std::string		tmp;
	size_t			index = 0;
	for (size_t i = 4; i != splitLine.size(); i++)
	{
		tmp += splitLine[i];
		if (i + 1 != splitLine.size())
			tmp += " ";
	}
	std::string		prompt;
	for (std::string::iterator ite = tmp.begin(); ite != tmp.end(); ite++, index++)
	{
		if (tmp[index] != '\'')
			prompt += tmp[index];
	}
	prompt.erase(prompt.size() - 3, prompt.size());
	return prompt;
}

void	wall_e::privmsgBot(std::vector<std::string> splitLine) const
{
	if (splitLine[3] != std::string(":") + BOT_PREFIX)
		return ;
	if (splitLine.size() <= 5)
		return ;
	printShit("#i %s %s", splitLine[0].substr(1).c_str(), "is trying to generate an image");
	std::string	prompt = cleanPrompt(splitLine);
	std::string	url = generateImg(prompt);
	if (url == "null\n")
		sendToServer(PRIVMSG("An error occured during image generation", splitLine[2]));
	else
	{
		url.erase(url.size() - 1);
		printShit("#i %s \"%s\"", "Image succesfully generated with the prompt:", prompt.c_str());
		sendToServer(PRIVMSG(SEND_LINK(url, prompt,splitLine[0].substr(1).c_str()), splitLine[2]));
	}
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
