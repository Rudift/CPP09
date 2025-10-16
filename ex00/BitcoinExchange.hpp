/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-16 14:31:27 by vdeliere          #+#    #+#             */
/*   Updated: 2025-10-16 14:31:27 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#  include "Colors.hpp"
#  include <iostream>
#  include <fstream>
#  include <string>
#  include <map>
#  include <exception>
#  include <cstdlib>

class BitcoinExchange{
	private:
		std::map<std::string, float> _data;
	public:
		//Coplien
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange& operator=(const BitcoinExchange &other);
		~BitcoinExchange();
		void	loadDatabase(std::string path);
};

bool	isLineValid(std::string line);
float	stringToFloat(std::string line);

#endif