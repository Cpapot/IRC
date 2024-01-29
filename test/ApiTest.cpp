#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>

# define CHECK_API_KEY(url, apiKey)			std::string("curl -s ") + url + std::string(" \"-H \"Authorization: Bearer ") + apiKey + std::string(" | jq '.error'\"")

# define CURL_REQUEST(prompt, url, apiKey)	std::string("curl -s ") + url + std::string("\
	-H \"Content-Type: application/json\" \
	-H \"Authorization: Bearer ") + apiKey + std::string("\" \
	-d \'{ \
	\"prompt\": \"") + prompt + std::string("\", \
	\"n\": 1, \
	\"size\": \"1024x1024\" \
	}\'")

# define BOTBUFFER	1024


int main(int argc, char **argv)
{

		std::string url = "https://api.openai.com/v1/images/generations";
		char *tmp = std::getenv("DALLE_API_KEY");
		std::string prompt = "Illustrate a scene from a Victorian masquerade ball with elaborate costumes. Use contrasting colors and soft lighting to accentuate the mysterious and festive atmosphere.";

		if (tmp == NULL)
			throw std::invalid_argument("bot::YouNeedToSetApiKey");

		std::string apiKey = tmp;
		apiKey.erase(apiKey.size() - 1, apiKey.size());
		std::string curlCommand = CURL_REQUEST(prompt, url, apiKey) + " | jq";

		FILE		*pipe = popen(curlCommand.c_str(), "r");

		if (!pipe)
		{
			std::cout << "broken pipe" << std::endl;
			return 0;
		}
		char buff[BOTBUFFER];

		std::string response;
		while (fgets(buff, 256, pipe) != NULL)
			response += buff;
		pclose(pipe);
		std::cout << response << std::endl;
}
