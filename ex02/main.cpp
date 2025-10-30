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

std::vector<int>	parsing(int ac, char **av){
	std::vector<int> vect;
	for (int i = 1 ; i < ac ; i++){
		for (size_t j = 0 ; av[i][j] != '\0' ; j++){
			if (!std::isdigit(av[i][j]))
				throw std::invalid_argument("Error");
		}
		vect.push_back(atoi(av[i]));
	}
	return (vect);
}

std::vector< std::pair<int, int> > makePairs(std::vector<int> container){
	std::vector< std::pair<int, int> > pairs;

	for (size_t i = 0 ; i + 1 < container.size() ; i++){
		int a = container[i];
		int b = container[i + 1];
		if (a < b)
			pairs.push_back(std::make_pair(a, b));
		else
			pairs.push_back(std::make_pair(b, a));
		i += 2;
	}
	return pairs;
}

int	main(int ac, char **av){
	if (ac < 2){
		std::cerr << RED + "Error" + RESET << std::endl;
		return (-1);
	}
	std::vector<int>	vect;
	try{
		vect = parsing(ac, av);
	}catch(std::exception &e){
		std::cerr << RED << e.what() << RESET << std::endl;
		return (-1);
	}
	std::cout << "Before: " << vect << std::endl;
	return (0);
}