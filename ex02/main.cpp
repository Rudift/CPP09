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
#include <cstdlib>

int	main(int ac, char **av){
	if (ac < 2){
		std::cerr << RED + "Error" + RESET << std::endl;
		return (-1);
	}
	PmergeMe merge;
	try{
		merge.parsing(ac, av);
		std::cout << "Before: " << merge.getVector() << std::endl;
		merge.doPairs();
		std::cout << "After: " << merge.getVector() << std::endl;
		std::cout << "Size of the main: " << merge.getVector().size() << std::endl;
	}catch(std::exception &e){
		std::cerr << RED << e.what() << RESET << std::endl;
		return (-1);
	}
	
	return (0);
}