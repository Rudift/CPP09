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

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe& other){
	_vector = other._vector;
	_deque = other._deque;
}

PmergeMe&	PmergeMe::operator=(const PmergeMe& other){
	if (this != &other){
		_vector = other._vector;
		_deque = other._deque;
	}
	return (*this);
}

PmergeMe::~PmergeMe(){}

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

//Member fonction
std::vector<int> vectoriser(int nb){
	std::vector<int> vect;
	vect.push_back(nb);
	return (vect);
}

void	PmergeMe::parsing(int ac, char **av){
	std::vector<std::vector<int> > vect;
	for (int i = 1 ; i < ac ; i++){
		for (size_t j = 0 ; av[i][j] != '\0' ; j++){
			if (!std::isdigit(av[i][j]))
				throw std::invalid_argument("Error");
		}
		_vector.push_back(vectoriser(atoi(av[i])));
	}
}

void PmergeMe::doPairs(){
	if (_vector.size() == 1)
		return ;
	
	
}

//Getters
std::vector<std::vector<int> > PmergeMe::getVector(){
	return(_vector);
}



// Implémentation de l'opérateur << pour std::vector<std::vector<int> >
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<int> >& container){
	std::vector<std::vector<int> >::const_iterator it = container.begin();
	std::vector<std::vector<int> >::const_iterator end = container.end();
	
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