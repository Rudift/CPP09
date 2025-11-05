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
#include <cstdlib>
#include "Colors.hpp"


class PmergeMe{

	private :
		std::vector<std::vector<int> >	_vector;
		std::deque<std::deque<int> >	_deque;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other); 
		PmergeMe&	operator=(const PmergeMe& other);
		~PmergeMe();

		//Member fonctions
		void	parsing(int ac, char **av);
		void	sortVector();
		
		//Fonctions for sorting vectors
		std::vector<int> handleOddElement();
		void	doPairing();
		void	separateWinnersAndLosers(std::vector<std::vector<int> >& winner, 
											std::vector<std::vector<int> >& looser, 
											size_t sizeElem);
		std::vector<size_t> generateJacobsthalOrder(size_t nbElements);
		void	insertLosersIntoWinners(std::vector<std::vector<int> >& winner,
										const std::vector<std::vector<int> >& looser,
										size_t sizeElem);
		void	insertOddElementBack(std::vector<std::vector<int> >& winner,
									const std::vector<int>& oddElement,
									size_t sizeElem);
		void	rebuildVector(const std::vector<std::vector<int> >& winner);

		//Getters
		std::vector<std::vector<int> > getVector();
		std::deque<std::deque<int> > getDeque();
};


//Operators overload
std::ostream& operator<<(std::ostream& os, const std::vector<int>& container);

std::ostream& operator<<(std::ostream& os, const std::deque<int>& container);

std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<int> >& container);

#endif