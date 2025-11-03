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

//Non-member fonction
std::vector<int> vectoriser(int nb){
	std::vector<int> vect;
	vect.push_back(nb);
	return (vect);
}

bool	isEmptyVector(const std::vector<int>& v){
	return (v.empty());
}

//Member fonction
void	PmergeMe::parsing(int ac, char **av){
	for (int i = 1 ; i < ac ; i++){
		for (size_t j = 0 ; av[i][j] != '\0' ; j++){
			if (!std::isdigit(av[i][j]))
				throw std::invalid_argument("Error");
		}
		_vector.push_back(vectoriser(atoi(av[i])));
	}
}

void PmergeMe::doPairs(){
	bool hasPaired = false;
	
	for (size_t i = 0 ; i < _vector.size() ; i+=2){
		if (i + 1 < _vector.size() && _vector[i].size() == _vector[i + 1].size()){
			if (_vector[i][_vector[i].size() - 1] > _vector[i + 1][_vector[i + 1].size() - 1])
				std::swap(_vector[i], _vector[i + 1]);
			_vector[i].insert(_vector[i].end(), _vector[i + 1].begin(), _vector[i + 1].end());
			_vector[i + 1].clear();
			hasPaired = true;
			//std::cout << "Max pair n*" << i/2 << " = " << _vector[i][_vector[i].size() - 1] << std::endl;
		}
	}
	_vector.erase(std::remove_if(_vector.begin(), _vector.end(), isEmptyVector), _vector.end());
	std::cout << "Pairing: " << _vector << std::endl;
	if (hasPaired && _vector.size() > 1) {
		this->doPairs();
	}
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