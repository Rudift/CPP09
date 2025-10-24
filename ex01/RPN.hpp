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

void	parsing (std::stack<int> &rpn, char *av);
int		doOperation(int a, int b, char op);
void	printStack(std::stack<int> s);

#endif