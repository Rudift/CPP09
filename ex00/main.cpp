/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-16 14:30:59 by vdeliere          #+#    #+#             */
/*   Updated: 2025-10-16 14:30:59 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int ac, char **av){
	(void) av;
	if (ac != 2){
		std::cout << RED + "Error: could not open file." + RESET << std::endl;
		return (0);
	}

	BitcoinExchange data;
	try{
		data.loadDatabase("data.csv"); //load the database
		data.handleInput(av[1]); //load the input and cross it with the database
	}catch (std::exception &e){
		std::cerr << RED + e.what() + RESET << std::endl;
		return(1);
	}
	return (0);
}