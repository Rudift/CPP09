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
	if (!isValidExt(path, "csv"))
		throw std::invalid_argument("Error: wrong file extension.");
	std::ifstream file(path.c_str());
	if (!file){
		throw std::invalid_argument(path + " not found");
	}
	std::cout << GREEN << path << " is open !" + RESET << std::endl;
	std::string	line;
	std::getline(file, line);
	while (std::getline(file, line)){
		size_t separator = line.find(',');
		std::string date = line.substr(0, separator);
		float rate = atof (line.substr(separator + 1).c_str());
		_data[date] = rate;
	}
	file.close();
	std::cout << GREEN + "Database successfully loaded" + RESET << std::endl;
	// for (std::map<std::string, float>::iterator it = _data.begin(); it != _data.end(); ++it){
	// 	 std::cout << "Clé : " << it->first << " -> Valeur : " << it->second << std::endl;
	// }
}

void	BitcoinExchange::handleInput(std::string path){
	if (!isValidExt(path, "txt")) // Verification of the extension of the file
		throw std::invalid_argument("Error: wrong file extension."); 

	std::ifstream file(path.c_str());
	if (!file)
		throw std::invalid_argument("Error: could not open file.");
	
	std::cout << GREEN << path << " is open !" + RESET << std::endl;
	std::string	line;
	std::getline(file, line);
	while (std::getline(file, line)){
		size_t separator = line.find('|');
		// if (separator == line.npos){
		// 	throw std::invalid_argument("Error: invalid line.");
		// 	continue;
		// }

		std::string date = line.substr(0, separator - 1);
		if (!isValidDate(date)){
			std::cerr << RED +"Error: bad input => " << line.substr(0, 10) << RESET << std::endl;
			continue;
		}
		std::string strValue = line.substr(separator + 2);
		float value = atof(strValue.c_str());
		if (!isValidValue(value))
			continue;
		std::cout << date << " => " << value << " = " << value * getRate(date) << std::endl;
	}
	file.close();
}

float	BitcoinExchange::getRate(std::string date){
	std::map<std::string, float>::const_iterator it = _data.lower_bound(date);

	//Case 1 : the date exist
	if (it != _data.end() && it->first == date)
		return it->second;

	//Case 2: lower_bound get back the first supperior date
	if (it == _data.begin()){
		throw std::runtime_error("Error: no exploitable date");
	}
	--it;
	return it->second;
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
	int endDay [13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		endDay[2] = 29;
	if (day > endDay[month] || day < 1)
		return (false);
	return (true);
}

bool isValidExt(std::string path, std::string ref){
	if (!(path.size() >= 3))
		return (false);
	std::string ext = path.substr(path.size() - 3);
	if (ext != ref)
		return (false);
	return (true);
}

bool isValidValue(float value){
	if (value < 0){
		std::cerr << RED + "Error: not a positive number." + RESET << std::endl;
		return (false);
	}
	if (value > 1000){
		std::cerr << RED + "Error: too large number." + RESET << std::endl;
		return (false);
	}
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

