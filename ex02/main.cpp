/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-27 13:07:18 by vdeliere          #+#    #+#             */
/*   Updated: 2025-10-27 13:07:18 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool isPositiv(char **av){
	for (int i = 1 ; av[i] ; i++){
		if (atoi(av[i]) < 0){
			std::cerr << RED + "Error: there is a negative number in the list" + RESET << std::endl;
			return(false);
		}
	}
	return (true);
}

bool isNum(char **av){
	for (int i = 1 ; av[i] ; i++){
		std::string str = av[i];
		for (size_t j = 0; j < str.length(); j++){
			if (!std::isdigit(str[j])){
				std::cerr << RED + "Error: there is a non-numeric character in the list" + RESET << std::endl;
				return(false);
			}
		}
	}
	return (true);
}

int	main(int ac, char **av){
	if (ac < 2){
		std::cerr << RED + "Error: too few arguments." + RESET << std::endl;
		return (-1);
	}
	std::vector<int>	vect;
	if (!isPositiv(av) || !isNum(av))
		return (-1);
	
	// Remplir le vecteur avec les arguments
	for (int i = 1; i < ac; i++){
		vect.push_back(atoi(av[i]));
	}
	
	std::cout << "Before: " << vect << std::endl;
	return (0);
}