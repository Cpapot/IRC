/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_e.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:46:17 by cprojean          #+#    #+#             */
/*   Updated: 2024/01/31 14:40:16 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_E_HPP
# define WALL_E_HPP

# include "ABot.hpp"

# define BOT_PREFIX		"W!"
# define FGETS_BOT_BUFFER	1024
# define API_KEY_INVALID			"The api key you gave is invalid."
# define API_KEY_ERROR				"To use DALLEBOT you need to export your open AI API key to the \"DALLE_API_KEY\" variable and restart the server."
# define PIPE_ERROR					"Broken pipe."
# define FGETS_ERROR				"fgets() crashed"
# define CURL_REQUEST(prompt, apiKey)	std::string("curl -s https://api.openai.com/v1/images/generations") + std::string("\
	-H \"Content-Type: application/json\" \
	-H \"Authorization: Bearer ") + apiKey + std::string("\" \
	-d \'{ \
	\"prompt\": \"") + prompt + std::string("\", \
	\"n\": 1, \
	\"size\": \"1024x1024\" \
	}\'")

class wall_e : public ABot
{
	private :
		bool			_botStatus;
		std::string		_apiKey;

		bool			setAndCheckApiKey(void);
		std::string		getStringFromPipe(FILE *pipe);
	public :
		std::string	generateImg(std::string prompt);
		wall_e(int clientSocket, server *serverPtr, char **argv);
		~wall_e(void);
		// bool routine() const;
};

#endif
