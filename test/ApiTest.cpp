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
		std::string curlCommand = CURL_REQUEST(prompt, url, apiKey) + " | jq -r '.data[0].url'";

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

/*

{
  "created": 1706709130,
  "data": [
    {
      "url": "https://oaidalleapiprodscus.blob.core.windows.net/private/org-kTJUP0w4SNlVHssysjijmEnz/user-dCu7ObpEMXZTTlgP7uS4AUVp/img-MoxLsfeCGKspjIwvf33Qnuok.png?st=2024-01-31T12%3A52%3A10Z&se=2024-01-31T14%3A52%3A10Z&sp=r&sv=2021-08-06&sr=b&rscd=inline&rsct=image/png&skoid=6aaadede-4fb3-4698-a8f6-684d7786b067&sktid=a48cca56-e6da-484e-a814-9c849652bcb3&skt=2024-01-31T09%3A28%3A50Z&ske=2024-02-01T09%3A28%3A50Z&sks=b&skv=2021-08-06&sig=YC9Srg%2Bcux%2BNFGejDKo%2BKTskChQ1YBMKQcvJmKnc6Ns%3D"
    }
  ]
}


*/
