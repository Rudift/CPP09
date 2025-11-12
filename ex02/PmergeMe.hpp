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

// Standard library includes
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
		void	sortDeque();
		
		//Fonctions for sorting vector
		std::vector<int> 	handleOddVector();
		void				doPairingVect();
		void				separateWinnersAndLosersVect(std::vector<std::vector<int> >& winner, std::vector<std::vector<int> >& looser, size_t sizeElem);
		std::vector<size_t> generateJacobsthalOrderVect(size_t nbElements);
		void				insertLosersIntoWinnersVect(std::vector<std::vector<int> >& winner, const std::vector<std::vector<int> >& looser, size_t sizeElem);
		void				insertOddVectorBack(std::vector<std::vector<int> >& winner, const std::vector<int>& oddElement, size_t sizeElem);
		void				rebuildVector(const std::vector<std::vector<int> >& winner);

		//Fonction for sorting deque
		std::deque<int> 	handleOddDeque();
		void				doPairingDeque();
		void				separateWinnersAndLosersDeq(std::deque<std::deque<int> >& winner, std::deque<std::deque<int> >& looser, size_t sizeElem);
		void				insertLosersIntoWinnersDeq(std::deque<std::deque<int> >& winner, const std::deque<std::deque<int> >& looser, size_t sizeElem);
	std::deque<size_t>	generateJacobsthalOrderDeq(size_t nbElements);
	size_t				binarySearchDeq(const std::deque<std::deque<int> >& deq, int elem, size_t nbElem);
		void				insertOddDequeBack(std::vector<std::vector<int> >& winner, const std::vector<int>& oddElement, size_t sizeElem);
		void				insertOddDequeBack(std::deque<std::deque<int> >& winner, const std::deque<int>& oddElement, size_t sizeElem);
		void				rebuildDeque(const std::deque<std::deque<int> >& winner);

		/**
		 * PmergeMe
		 * --------
		 * Small class implementing a pairwise merge-sort variant (Pmerge).
		 * It stores the input numbers as containers of size-1 vectors/deques
		 * and performs pairing, winner/looser separation and insertion using a
		 * Jacobsthal-based order. The class provides both vector and deque
		 * implementations for comparison.
		 */

		// Getters: return const references to avoid copying large containers
		const std::vector<std::vector<int> >&    getVector() const;
		const std::deque<std::deque<int> >&    getDeque() const;
	};

std::deque<int> dequeiser(int nb);

// Operators overload for printing containers (defined in PmergeMe.cpp)
std::ostream& operator<<(std::ostream& os, const std::vector<int>& container);
std::ostream& operator<<(std::ostream& os, const std::deque<int>& container);
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<int> >& container);
std::ostream& operator<<(std::ostream& os, const std::deque<std::deque<int> >& container);

#endif