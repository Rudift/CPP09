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

void	parsing (std::stack<int> &rpn, char *arg){
	for (int i = 0; arg[i]; i++){
		if (std::isdigit(arg[i])){
			if (std::isdigit(arg[i + 1]))
				throw std::invalid_argument("Error: only number between 0 and 9 include are autorized.");
			rpn.push(arg[i] - 48);
		}
		else if (arg[i] == ' ')
			continue;
		else{
			if (rpn.size() < 2)
				throw std::invalid_argument("Error: wrong syntaxe.");
			int b = rpn.top(); rpn.pop();
			int a = rpn.top(); rpn.pop();
			rpn.push(doOperation(a, b, arg[i]));
		}
	}
}

int		doOperation(int a, int b, char op){
	char operators[4] = {'+', '-', '*', '/'};
	int i = 0;
	while (op != operators[i])
		i++;
	switch (i){
		case 0:
			return (a + b);
		case 1:
			return (a - b);
		case 2:
			return (a * b);
		case 3:
			return (a / b);
		default:
			throw std::invalid_argument("Error: Wrong syntaxe.");
	}
}


void	printStack(std::stack<int> s){
	while (!s.empty()){
		std::cout << s.top() << std::endl;
		s.pop();
	}
}
