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

std::ostream&	operator<<(std::ostream& os, const std::list<int>& list){
	for (std::list<int>::const_iterator it = list.begin(); it != list.end(); ++it){
		os << *it;
		std::list<int>::const_iterator next = it;
		++next;
		if (next != list.end())
			os << " ";
	}
	return os;
}

