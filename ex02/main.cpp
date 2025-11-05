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
	PmergeMe merge;
	try{
		merge.parsing(ac, av);
		std::cout << "Before: " << merge.getVector() << std::endl;
		clock_t beginVect = clock();
		merge.sortVector();
		clock_t endVect = clock();
		double	timeVect = (double(endVect - beginVect) / CLOCKS_PER_SEC) * 1000000;
		std::cout << "After: " << merge.getVector() << std::endl;
		std::cout << "Time to process a range of " << merge.getVector().size() << " elements with std::vector: " << timeVect << "us" << std::endl;
	}catch(std::exception &e){
		std::cerr << RED << e.what() << RESET << std::endl;
		return (-1);
	}
	
	return (0);
}