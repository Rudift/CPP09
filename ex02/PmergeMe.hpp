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
#include <utility>
#include "Colors.hpp"


class PmergeMe{

	private :
		std::vector<std::vector<int> >	_vector;
		std::deque<int>		_deque;

		template<typename T>
		T fordJohnsonSort(T container);
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe&	operator=(const PmergeMe& other);
		~PmergeMe();

		//Member fonctions
		void	parsing(int ac, char **av);
		void	doPairs();

		//Getters
		std::vector<std::vector<int> > getVector();

		
};


// Surcharge spécifique pour std::vector<int>
std::ostream& operator<<(std::ostream& os, const std::vector<int>& container);

// Surcharge spécifique pour std::deque<int>
std::ostream& operator<<(std::ostream& os, const std::deque<int>& container);

// Surcharge spécifique pour std::vector< std::vector<int> >
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<int> >& container);

#endif