/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-27 13:07:33 by vdeliere          #+#    #+#             */
/*   Updated: 2025-10-27 13:07:33 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <cctype>
#include <ctime>
#include "Colors.hpp"


//Parsing
bool	isDigit(std::string s);

// Surcharge spécifique pour std::vector<int>
std::ostream& operator<<(std::ostream& os, const std::vector<int>& container);

// Surcharge spécifique pour std::deque<int>
std::ostream& operator<<(std::ostream& os, const std::deque<int>& container);

#endif