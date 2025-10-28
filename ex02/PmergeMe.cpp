/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-27 13:09:52 by vdeliere          #+#    #+#             */
/*   Updated: 2025-10-27 13:09:52 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool	isDigit(std::string s){
	for (size_t i = 0; i < s.size(); i++){
		if (!isdigit(s[i]))
			return false;
	}
	return true;
}

// Implémentation de l'opérateur << pour std::vector<int>
std::ostream& operator<<(std::ostream& os, const std::vector<int>& container){
	std::vector<int>::const_iterator it = container.begin();
	std::vector<int>::const_iterator end = container.end();
	
	while (it != end)
	{
		os << *it;
		++it;
		if (it != end)
			os << " ";
	}
	return (os);
}

// Implémentation de l'opérateur << pour std::deque<int>
std::ostream& operator<<(std::ostream& os, const std::deque<int>& container){
	std::deque<int>::const_iterator it = container.begin();
	std::deque<int>::const_iterator end = container.end();
	
	while (it != end)
	{
		os << *it;
		++it;
		if (it != end)
			os << " ";
	}
	return (os);
}