/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_e.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:46:17 by cprojean          #+#    #+#             */
/*   Updated: 2024/01/31 13:38:35 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_E_HPP
# define WALL_E_HPP

# include "ABot.hpp"

class wall_e : public ABot
{
	private :
		bool			_BotStatus;
		std::string		_apiKey;

		void			setAndCheckApiKey(void);
	public :
			wall_e(int clientSocket, server *serverPtr, char **argv);
			~wall_e(void);
			// bool routine() const;
};

#endif
