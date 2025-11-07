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
		std::cerr << RED + "Error" + RESET << std::endl;
		return (-1);
	}

	std::cout << MAGENTA << "\n\n/====== WELCOME TO PMERGEME ======/" << RESET << std::endl << std::endl;
	PmergeMe merge;
	try{
		merge.parsing(ac, av);
		std::cout << RED + "Before: " + RESET << merge.getVector() << std::endl;
		
		// Test with vector
		clock_t beginVect = clock();
		merge.sortVector();
		clock_t endVect = clock();
		double	timeVect = (double(endVect - beginVect) / CLOCKS_PER_SEC) * 1000000;
		std::cout << GREEN + "After: " + RESET << merge.getVector() << std::endl;
		std::cout << YELLOW << "Time to process a range of " << RED << merge.getVector().size() << YELLOW << " elements with std::vector: "<< RED << timeVect << "us" << RESET << std::endl;
		
		// Test with deque
		clock_t beginDeq = clock();
		merge.sortDeque();
		clock_t endDeq = clock();
		double	timeDeq = (double(endDeq - beginDeq) / CLOCKS_PER_SEC) * 1000000;
		std::cout << YELLOW << "Time to process a range of " << RED << merge.getDeque().size() << YELLOW << " elements with std::deque: " << RED << timeDeq << "us" << RESET << std::endl << std::endl;
	}catch(std::exception &e){
		std::cerr << RED << e.what() << RESET << std::endl;
		return (-1);
	}
	
	return (0);
}