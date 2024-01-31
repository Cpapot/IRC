/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverLogs.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:22:16 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/30 11:11:34 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERLOGS_HPP
# define SERVERLOGS_HPP

# include "Irc.hpp"


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
