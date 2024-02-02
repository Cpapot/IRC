/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:05:43 by cprojean          #+#    #+#             */
/*   Updated: 2024/02/02 10:17:53 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <sys/types.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <string>
# include <iostream>
# include <unistd.h>
# include <arpa/inet.h>

int main() {
	// Création du socket client
	/*if (argc != 3)
		std::cout << "Bots : I need only a port and a password !" << std::endl;*/

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

	// Fermeture du socket client
	close(clientSocket);

	return 0;
}
