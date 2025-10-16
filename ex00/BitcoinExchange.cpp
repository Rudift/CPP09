/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-16 14:36:29 by vdeliere          #+#    #+#             */
/*   Updated: 2025-10-16 14:36:29 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

//Coplien

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other){
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other){
	if (this != &other)
		_data = other._data;
	return (*this);
}

BitcoinExchange::~BitcoinExchange(){}

//Member fonctions

void	BitcoinExchange::loadDatabase(std::string path){
	std::ifstream file(path.c_str());
	if (!file){
		throw std::invalid_argument(path + " not found");
	}
	std::cout << GREEN << path << " is open !" + RESET << std::endl;
	std::string	line;
	while (std::getline(file, line)){
		std::cout << line << std::endl;
	}
	file.close();
}

//Non-member fonctions

// bool isLineValid(std::string line){

// }

float	stringToFloat(std::string line){
	std::string::size_type	pos = line.find(',');
	if (pos != std::string::npos){
		std::string	float_str = line.substr(pos + 1);
		
		float value = static_cast<float>(atof(float_str.c_str()));
		return(value);
	}
	throw std::invalid_argument("Error : wrong value format");
}

