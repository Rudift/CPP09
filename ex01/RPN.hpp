/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-24 09:33:32 by vdeliere          #+#    #+#             */
/*   Updated: 2025-10-24 09:33:32 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <stack>
#include <exception>
#include "Colors.hpp"

void	dispatch(std::stack<unsigned int> &numbers, std::stack<char> &operators, char **av);
bool	isOperator(char c);

template<typename T>
void	printStack(std::stack<T> s){
	std::cout << YELLOW + "Content of the stack from top to down" + RESET << std::endl;
	while (!s.empty()){
		std::cout << "caca" << std::endl;
		std::cout << s.top() << std::endl;
		s.pop();
	}
}

#endif