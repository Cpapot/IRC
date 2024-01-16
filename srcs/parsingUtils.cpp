/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingUtils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:07:45 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/16 18:03:50 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cstring>
#include <vector>

void tokenize(std::string const &str, const char delim, std::vector<std::string> &out)
{
	size_t start;
	size_t end = 0;
	std::string	tmp = str;

	while ((start = tmp.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = tmp.find(delim, start);
		out.push_back(tmp.substr(start, end - start));
	}
	//delete last char for first split
	if (delim == '\n')
	{
		for (size_t i = 0; i != out.size(); i++)
		{
			if (out[i][out[i].size() - 1] <= 20)
				out[i].erase(out[i].size() - 1);
		}
	}
}
