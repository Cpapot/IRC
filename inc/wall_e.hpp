/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_e.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:46:17 by cprojean          #+#    #+#             */
/*   Updated: 2024/02/07 17:41:12 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_E_HPP
# define WALL_E_HPP

# include "ABot.hpp"

# define BOT_PREFIX		"W!"
# define FGETS_BOT_BUFFER	1024
# define API_KEY_INVALID			std::string("The api key you gave is invalid.")
# define API_KEY_ERROR				std::string("To use DALLEBOT you need to export your open AI API key to the \"DALLE_API_KEY\" variable.")
# define PIPE_ERROR					std::string("Broken pipe.")
//# define FGETS_ERROR				std::string("fgets() crashed")
# define DALL_E_URL					std::string("https://api.openai.com/v1/images/generations")
# define CURL_REQUEST(prompt, url, apiKey)	std::string("curl -s ") + url + std::string("\
	-H \"Content-Type: application/json\" \
	-H \"Authorization: Bearer ") + apiKey + std::string("\" \
	-d \'{ \
	\"model\": \"dall-e-3\", \
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
		std::string		getStringFromPipe(FILE *pipe) const;
	public :
		std::string	generateImg(std::string prompt) const;
		wall_e(int argc, char **argv);
		~wall_e(void);
		void	privmsgBot(std::vector<std::string> splitLine) const;
};

#endif
