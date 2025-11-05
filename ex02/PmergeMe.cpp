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

size_t	binarySearch(std::vector<std::vector<int> > vect, int elem, size_t nbElem){
	if (nbElem == 0)
		return 0;

	size_t sizeElem = vect[0].size();
	int left = 0;
	int right = nbElem - 1;
	int mid = 0;

	while (left <= right) {
		mid = left + (right - left) / 2;

		// Compare l'élément recherché avec le dernier élément de la ligne 'mid'
		if (vect[mid][sizeElem - 1] < elem)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return left;
}

size_t	jacobsthalGenerator(size_t sizeElem, size_t index){
	size_t	jacobSequence[sizeElem];

	jacobSequence[0] = 0;
	jacobSequence[1] = 1;
	for (size_t i = 2 ; i < sizeElem ; i++){
		jacobSequence[i] = jacobSequence[i - 1] + 2 * jacobSequence[i - 2];
	}
	
	// Afficher le contenu du tableau manuellement
	std::cout << "Jacobsthal sequence: ";
	for (size_t i = 0; i < sizeElem; i++) {
		std::cout << jacobSequence[i];
		if (i < sizeElem - 1) std::cout << " ";
	}
	std::cout << std::endl;
	
	return (jacobSequence[index]);
}


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
	std::vector<int> numbers;
	
	for (int i = 1 ; i < ac ; i++){
		for (size_t j = 0 ; av[i][j] != '\0' ; j++){
			if (!std::isdigit(av[i][j]))
				throw std::invalid_argument("Error");
		}
		int number = atoi(av[i]);
		
		for (size_t k = 0; k < numbers.size(); k++){
			if (numbers[k] == number)
				throw std::invalid_argument("Error");
		}
		
		numbers.push_back(number);
		_vector.push_back(vectoriser(number));
	}
}

void PmergeMe::sortVector(){
	bool hasPaired = false;
	std::vector<int> oddVector;
	size_t lastElem = _vector.size() - 1;
	bool hasOdd = false;
	if (lastElem % 2 == 0 && lastElem != 0)
	{
		oddVector =(_vector[lastElem]);
		hasOdd = true;
		_vector.pop_back();
		std::cout <<"Reste: "<< oddVector<<std::endl;
		std::cout <<"Vector: "<< _vector <<std::endl;
	}
	for (size_t i = 0 ; i < _vector.size() ; i+=2){
		if (i + 1 < _vector.size() && _vector[i].size() == _vector[i + 1].size()){
			if (_vector[i][_vector[i].size() - 1] > _vector[i + 1][_vector[i + 1].size() - 1])
				std::swap(_vector[i], _vector[i + 1]);
			_vector[i].insert(_vector[i].end(), _vector[i + 1].begin(), _vector[i + 1].end());
			_vector[i + 1].clear();
			hasPaired = true;
		}

	}

	_vector.erase(std::remove_if(_vector.begin(), _vector.end(), isEmptyVector), _vector.end());



	std::cout << "Pairing: " << _vector << std::endl << std::endl;
	if (hasPaired && _vector.size() > 1)
		this->sortVector();
	

	//defusionner les pair  en main et pend
	std::vector<std::vector<int> > winner;
	std::vector<std::vector<int> > looser;
	size_t sizeElem	= _vector[0].size();
	if (sizeElem == 1)
		return ;
	else
		sizeElem /= 2;	
	
	for (size_t i = 0; i < _vector.size(); i++){
		if (_vector[i].size() == sizeElem * 2){
			std::vector<int> tmpWin;
			std::vector<int> tmpLoose;

			for(size_t j = 0 ; j < sizeElem ; j++){
				tmpLoose.push_back(_vector[i][j]);
				tmpWin.push_back(_vector[i][j + sizeElem]);
			}
			winner.push_back(tmpWin);
			looser.push_back(tmpLoose);
		}
	}
	std::cout << "Winner: " << winner << std::endl ;
	std::cout << "Looser: " << looser << std::endl ;

	//2 inserer pend dans main
	for (size_t i = 0; i < looser.size(); i++){
		jacobsthalGenerator(sizeElem, i);
		size_t index = i; // inserer sequence de Jacobsthal ici
		int needle = _vector[index][2 * sizeElem - 1];
		int indexWin;
		for (size_t j = 0; j < winner.size(); j++) {
			if (needle == winner[j][sizeElem - 1])
			{
				indexWin = j;
			}
		}

		size_t indexInsert = binarySearch(winner, looser[index][sizeElem - 1], indexWin +1);
		winner.push_back(looser[index]);
		std::rotate(winner.begin() + indexInsert, winner.end() - 1, winner.end());
		std::cout << "--- "<<winner<< "indexWin = "<< indexWin<<std::endl;
	
	}
	if (hasOdd)
	{
		std::cout << "reste : " << oddVector<< std::endl;
		 size_t indexInsert = binarySearch(winner, oddVector[sizeElem - 1], winner.size());
		 winner.push_back(oddVector);
		 std::rotate(winner.begin() + indexInsert, winner.end() - 1, winner.end());
		 std::cout << winner<< std::endl;
		//winner.push_back(oddVector);
	}


	_vector.clear();
	for (size_t i = 0; i < winner.size(); i++){
		std::vector<int> tmp;
		for (size_t j = 0 ; j < winner[i].size(); j++)
		{
			tmp.push_back(winner[i][j]);
		}
			_vector.push_back(tmp);
	}

	std::cout << "Vector: " << _vector << std::endl;
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
		os <<"(";
		os << *it;
		++it;
		os << ") ";
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