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
			if (arg[i + 1] && std::isdigit(arg[i + 1]))
				throw std::invalid_argument("Error: Only single digit numbers (0-9) are authorized.");
			rpn.push(arg[i] - '0'); 
		}else if (arg[i] == ' ')
			continue;
		else if (arg[i] == '+' || arg[i] == '-' || arg[i] == '*' || arg[i] == '/'){
			if (rpn.size() < 2)
				throw std::invalid_argument("Error: Insufficient operands for operator.");
			int b = rpn.top(); rpn.pop();
			int a = rpn.top(); rpn.pop();
			try {
				rpn.push(doOperation(a, b, arg[i]));
			} catch (const std::exception& e) {
				rpn.push(a);
				rpn.push(b);
				throw;
			}
		}else{
			throw std::invalid_argument("Error: Invalid character in expression.");
		}
	}
	
	if (rpn.size() != 1)
		throw std::invalid_argument("Error: Invalid RPN expression - wrong number of operands.");
}

int		doOperation(int a, int b, char op){
	long	res = 0;
	
	if (op != '+' && op != '-' && op != '*' && op != '/')
		throw std::invalid_argument("Error: Invalid operator.");
		
	switch (op){
		case '+':
			if ((b > 0 && a > std::numeric_limits<int>::max() - b) ||
				(b < 0 && a < std::numeric_limits<int>::min() - b))
				throw std::invalid_argument("Error: Addition overflow.");
			res = static_cast<long>(a) + static_cast<long>(b);
			break;
		case '-':
			if ((b < 0 && a > std::numeric_limits<int>::max() + b) ||
				(b > 0 && a < std::numeric_limits<int>::min() + b))
				throw std::invalid_argument("Error: Subtraction overflow.");
			res = static_cast<long>(a) - static_cast<long>(b);
			break;
		case '*':
			if (a != 0 && b != 0) {
				if ((a > 0 && b > 0 && a > std::numeric_limits<int>::max() / b) ||
					(a > 0 && b < 0 && b < std::numeric_limits<int>::min() / a) ||
					(a < 0 && b > 0 && a < std::numeric_limits<int>::min() / b) ||
					(a < 0 && b < 0 && a < std::numeric_limits<int>::max() / b))
					throw std::invalid_argument("Error: Multiplication overflow.");
			}
			res = static_cast<long>(a) * static_cast<long>(b);
			break;
		case '/':
			if (b == 0)
				throw std::invalid_argument("Error: Division by zero is forbidden.");
			if (a == std::numeric_limits<int>::min() && b == -1)
				throw std::invalid_argument("Error: Division overflow.");
			res = static_cast<long>(a) / static_cast<long>(b);
			break;
		default:
			throw std::invalid_argument("Error: Invalid operator.");
			break;
	}
	
	// Vérification finale que le résultat tient dans un int
	if (res > std::numeric_limits<int>::max() || res < std::numeric_limits<int>::min())
		throw std::invalid_argument("Error: Result out of int range.");
		
	return static_cast<int>(res);
}


void	printStack(std::stack<int> s){
	while (!s.empty()){
		std::cout << s.top() << std::endl;
		s.pop();
	}
}
