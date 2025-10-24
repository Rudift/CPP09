/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-24 09:36:05 by vdeliere          #+#    #+#             */
/*   Updated: 2025-10-24 09:36:05 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

void	dispatch(std::stack<unsigned int> &numbers, std::stack<char> &operators, char **av){
	for(int i = 1 ; av[1][i]; i++){
		if (std::isdigit(av[1][i])){
			numbers.push(av[1][i] - 48);
		}
		else if (isOperator(av[1][i]))
			operators.push(av[1][i]);
		else if (av[1][i] == ' ')
			continue;
		else
			throw std::invalid_argument("Error: the operation contain an invalid character");
	}
}

bool	isOperator(char c){
	return (c == '+' || c == '-' || c == '*' || c == '/');
}