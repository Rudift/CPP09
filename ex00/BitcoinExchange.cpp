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
	if (!isValidExt(path))
		throw std::invalid_argument("Error: wrong file extension");
	std::ifstream file(path.c_str());
	if (!file){
		throw std::invalid_argument(path + " not found");
	}
	std::cout << GREEN << path << " is open !" + RESET << std::endl;
	std::string	line;
	while (std::getline(file, line)){
		std::cout << line << std::endl;
		if (!isValidDate(line.substr(0, 10)))
			throw std::invalid_argument("Error: bad input => " + line.substr(0, 10));
		else
			std::cout << "good" << std::endl;
	}
	file.close();
}

//Non-member fonctions

bool isValidDate(std::string date){
	if (date.size() != 10)
		return (false);
	if (date.substr(4, 1) != "-" || date.substr(7, 1) != "-")
		return (false);

	int	year = atoi(date.substr(0, 4).c_str());
	int	month = atoi(date.substr(5, 2).c_str());
	int	day = atoi(date.substr(8, 2).c_str());

	if (year > 2025 || year < 0)
		return (false);
	if (month > 12 || month < 1)
		return (false);
	if (day > 31 || day < 1)
		return (false);
	return (true);
}

bool isValidExt(std::string path){
	if (!(path.size() >= 3))
		return (false);
	std::string ext = path.substr(path.size() - 3);
	if (ext != "txt" && ext != "csv")
		return (false);
	return (true);
}

float	stringToFloat(std::string line){
	std::string::size_type	pos = line.find(',');
	if (pos != std::string::npos){
		std::string	float_str = line.substr(pos + 1);
		
		float value = static_cast<float>(atof(float_str.c_str()));
		return(value);
	}
	throw std::invalid_argument("Error: wrong value format");
}

