/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverLogs.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:22:16 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/31 13:28:09 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERLOGS_HPP
# define SERVERLOGS_HPP

# include <fstream>
# include <sstream>
# include <cstdlib>
# include <string>
# include <ctime>
# include <iostream>


# define LOGS_TABULATION		std::string("				")

class serverLogs
{
private:
	std::ofstream	_out;
public:
	void	receive(std::string messageReceive, int source);
	void	sent(std::string messageSent, int target);

	std::string	getTime(void);
	serverLogs(int port);
	~serverLogs();
};

#endif
