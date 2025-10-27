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
#include <list>
#include <deque>
#include <cctype>
#include "Colors.hpp"


//Parsing
bool	isDigit(std::string s){
	for (int i = 0; i < s.size(); i++){
		if (!isdigit(s[i]))
			return false;
	}
	return true;
}

//Insertion overload
std::ostream&	operator<<(std::ostream& os, const std::list<int>& list); 

#endif