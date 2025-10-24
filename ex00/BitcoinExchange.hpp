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
#  include <stdlib.h>

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
		void	handleInput(std::string path);
		float	getRate(std::string date);
};

bool	isValidExt(std::string ext, std::string ref);
bool	isValidDate(std::string date);
bool	isValidValue(float value);

#endif