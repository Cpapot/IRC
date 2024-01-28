/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dalleBot.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:57:22 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/28 17:15:05 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DALLEBOT_HPP
# define DALLEBOT_HPP

# include <iostream>
# include "print.hpp"
# include <cstdlib>

# define DALLE_URL					"https://api.openai.com/v1/images/generations"
# define DALLE_JSON_PROMPT(prompt)	"{\n" +	\
									"    \"prompt\": \"" + prompt + "\",\n" +	\
									"    \"n\": 1,\n" +	\
									"    \"size\": \"1024x1024\"\n" +	\
									"}"

# define API_KEY_ERROR				"To use DALLEBOT you need to export your open AI API key to the \"DALLE_API_KEY\" variable and restart the server."


class dalleBot
{
private:
	bool			_apiIsReady;

	char			*_apiKey;

public:
	dalleBot(void);
	~dalleBot();
};

dalleBot::dalleBot(void)
{
	_apiKey = std::getenv("DALLE_API_KEY");
	if (_apiKey == NULL)
	{
		_apiIsReady = false;
		printShit("#e %s", API_KEY_ERROR);
	}
	else
		_apiIsReady = true;
}

dalleBot::~dalleBot()
{
}


#endif
