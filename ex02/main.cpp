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

int	main(int ac, char **av){
	if (ac < 2){
		std::cerr << RED + "Error: too few arguments." + RESET << std::endl;
		return (-1);
	}
	std::list<int>	list;
	for (int i = 1 ; av[i] ; i++){
		if (atoi(av[i]) < 0){
			std::cerr << RED + "Error: ther is a negativ number in the list" + RESET << std::endl;
			return(-1);
		}
		list.push_back(atoi(av[i]));
	}
	std::cout << "Before: " << list << std::endl;
}