#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

void	testmsg(int clientSocket)
{
	std::string msg("Bonjour serveur !!!");
	if (send(clientSocket, msg.c_str(), msg.length(), 0) == -1)
		std::cout << "echec de l'envoi" << std::endl;
}

//!!!!!!!!TEST GENERE AVEC CHATGPT!!!!!!!!
int main() {
	// Création du socket client
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1) {
		std::cerr << "Erreur lors de la création du socket client." << std::endl;
		return -1;
	}

	// Configuration de l'adresse du serveur
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Adresse IP du serveur (localhost dans cet exemple)
	serverAddress.sin_port = htons(6667); // Port d'écoute du serveur (même que dans le serveur)

	// Connexion au serveur
	if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
		std::cerr << "Erreur lors de la connexion au serveur." << std::endl;
		close(clientSocket);
		return -1;
	}

	std::cout << "Connecté au serveur." << std::endl;

	// À ce stade, vous pouvez échanger des données avec le serveur en utilisant clientSocket.

	testmsg(clientSocket);

	// Fermeture du socket client
	close(clientSocket);

	return 0;
}
