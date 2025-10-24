/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-24 11:05:34 by vdeliere          #+#    #+#             */
/*   Updated: 2025-10-24 11:05:34 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int ac, char **av){
	if (ac != 2){
		std::cerr << RED + "<Usage>: ./RPN \"your operation in RPN\"" + RESET << std::endl;
		return (-1);
	}
	std::stack<int>	rpn;
	try{
		parsing(rpn, av[1]);
		printStack(rpn);
	}catch(std::exception &e){
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	return (0);
}