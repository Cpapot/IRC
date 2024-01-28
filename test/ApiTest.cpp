#include <curl/curl.h>
#include <iostream>
#include <cstdlib>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

int main()
{
	CURL	*curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if (curl)
	{

		const char* url = "https://api.openai.com/v1/images/generations";
		const char* apiKey = std::getenv("DALLE_API_KEY");
		std::string prompt = "a photo of a happy corgi puppy sitting and facing forward, studio light, longshot";
        const char* jsonData =
            "{\n"
            "    \"prompt\": \"a photo of a happy corgi puppy sitting and facing forward, studio light, longshot\",\n"
            "    \"n\": 1,\n"
            "    \"size\": \"1024x1024\"\n"
            "}";


		if (apiKey == NULL)
			throw std::invalid_argument("bot::YouNeedToSetApiKey");

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData);

		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "Content-Type: application/json");
		char authHeader[100];
		sprintf(authHeader, "Authorization: Bearer %s", apiKey);
		headers = curl_slist_append(headers, authHeader);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);



		std::string response;
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		// Exécuter la requête
		res = curl_easy_perform(curl);

		// Vérifier les erreurs
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		} else {
			// Afficher la réponse
			std::cout << "Réponse de l'API : " << response << std::endl;
		}

		// Libérer les ressources
		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);
		curl_global_cleanup();
	}
}
