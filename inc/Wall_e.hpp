/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wall_e.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:46:17 by cprojean          #+#    #+#             */
/*   Updated: 2024/01/30 17:17:12 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_E_HPP
# define WALL_E_HPP

# include "Irc.hpp"

class Wall_e : public ABot
{
	private :
	
	public :
			Wall_e(int clientSocket, server *serverPtr, char **argv);
			~Wall_e(void);
			// bool routine() const;
};

#endif