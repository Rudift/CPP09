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
#include <cerrno>
#include <climits>

// Canonical
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

// ============ VECTOR ============
std::vector<int> vectoriser(int nb){
	std::vector<int> vect;
	vect.push_back(nb);
	return (vect);
}

bool	isEmptyVector(const std::vector<int>& v){
	return (v.empty());
}

bool	isEmptyDeque(const std::deque<int>& d){
	return (d.empty());
}

size_t	binarySearchVect(const std::vector<std::vector<int> >& vect, int elem, size_t nbElem){
	if (nbElem == 0 || vect.empty())
		return 0;

	size_t sizeElem = vect[0].size();
	int left = 0;
	int right = nbElem - 1;
	int mid = 0;

	while (left <= right) {
		mid = left + (right - left) / 2;

		// Compare the search element with the last one of the 'mid' line
		if (vect[mid][sizeElem - 1] < elem)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return (left);
}

PmergeMe::~PmergeMe(){}

//Member fonction
void	PmergeMe::parsing(int ac, char **av){
	std::vector<int> numbers;

	for (int i = 1 ; i < ac ; i++){
		char *endptr = NULL;
		errno = 0;
		long val = std::strtol(av[i], &endptr, 10);
		// Check for parsing errors
		if (endptr == av[i] || *endptr != '\0' || errno == ERANGE || val < INT_MIN || val > INT_MAX)
			throw std::invalid_argument(std::string("Invalid number: ") + av[i]);
		int number = static_cast<int>(val);

		for (size_t k = 0; k < numbers.size(); k++){
			if (numbers[k] == number)
				throw std::invalid_argument(std::string("Duplicate number: ") + av[i]);
		}

		numbers.push_back(number);
		_vector.push_back(vectoriser(number));
		_deque.push_back(dequeiser(number));
	}
}

void PmergeMe::sortVector(){
	//Step 1: Handle the odd Element if there is one
	std::vector<int> oddElement = handleOddVector();
	bool hasOdd = !oddElement.empty();
	
	//Step 2: Do the recursive pairing;
	doPairingVect();
	
	//Step 3: separate the winner and the looser
	std::vector<std::vector<int> > winner;
	std::vector<std::vector<int> > looser;
	size_t sizeElem = _vector[0].size();
	
	if (sizeElem == 1){
		return; // Sorting is finish
	}
	
	sizeElem /= 2;
	separateWinnersAndLosersVect(winner, looser, sizeElem);
	
	// Step 4: Use Jacobsthal to insert loosers into winners
	insertLosersIntoWinnersVect(winner, looser, sizeElem);
	
	// Step 5: Insert the odd element if he exist
	if (hasOdd) {
		insertOddVectorBack(winner, oddElement, sizeElem);
	}
	
	// Step 6: Reconstruct the final vector
	rebuildVector(winner);
}

std::vector<int> PmergeMe::handleOddVector(){
	std::vector<int> oddElement;
	if (_vector.empty())
		return oddElement;

	size_t lastElem = _vector.size() - 1;
    
	if (lastElem % 2 == 0 && lastElem != 0) {
		oddElement = _vector[lastElem];
		_vector.pop_back();
	}
    
	return oddElement;
}

void PmergeMe::doPairingVect(){
	bool hasPaired = false;
	
	for (size_t i = 0; i < _vector.size(); i += 2){
		if (i + 1 < _vector.size() && _vector[i].size() == _vector[i + 1].size()){
			if (_vector[i][_vector[i].size() - 1] > _vector[i + 1][_vector[i + 1].size() - 1])
				std::swap(_vector[i], _vector[i + 1]);
			_vector[i].insert(_vector[i].end(), _vector[i + 1].begin(), _vector[i + 1].end());
			_vector[i + 1].clear();
			hasPaired = true;
		}
	}
	
	_vector.erase(std::remove_if(_vector.begin(), _vector.end(), isEmptyVector), _vector.end()); // Delete the empty vectors

	if (hasPaired && _vector.size() > 1)
		this->sortVector();
}

void PmergeMe::separateWinnersAndLosersVect(std::vector<std::vector<int> >& winner, std::vector<std::vector<int> >& looser, size_t sizeElem){
	for (size_t i = 0; i < _vector.size(); i++){
		if (_vector[i].size() == sizeElem * 2) {
			std::vector<int> tmpWin;
			std::vector<int> tmpLoose;

			for (size_t j = 0; j < sizeElem; j++) {
				tmpLoose.push_back(_vector[i][j]);
				tmpWin.push_back(_vector[i][j + sizeElem]);
			}
			winner.push_back(tmpWin);
			looser.push_back(tmpLoose);
		}
	}
}

std::vector<size_t> PmergeMe::generateJacobsthalOrderVect(size_t nbElements){
	std::vector<size_t> insertionOrder;

	// Generate the Jacobsthal sequence up to the needed count
	// We include nbElements + 2 terms to safely compute insertion positions.
	std::vector<size_t> jacobsthal;
	if (nbElements == 0)
		return insertionOrder;

	jacobsthal.push_back(0);
	jacobsthal.push_back(1);

	size_t maxNeeded = nbElements + 2;
	for (size_t i = 2; i < maxNeeded; i++){
		size_t next = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];
		jacobsthal.push_back(next);
	}

	// Create the insertion order with Jacobsthal numbers.
	// We mark which indexes have been inserted to avoid duplicates.
	std::vector<bool> inserted(nbElements, false);

	for (size_t jacobIndex = 2; jacobIndex < jacobsthal.size(); jacobIndex++){
		size_t currentJacob = jacobsthal[jacobIndex];
		size_t prevJacob = jacobsthal[jacobIndex - 1];

		for (size_t pos = std::min(currentJacob, nbElements); pos > prevJacob && pos > 0; pos--){
			size_t index = pos - 1;
			if (index < nbElements && !inserted[index]){
				insertionOrder.push_back(index);
				inserted[index] = true;
			}
		}
	}

	for (size_t i = 0; i < nbElements; i++){
		if (!inserted[i]) {
			insertionOrder.push_back(i);
		}
	}

	return insertionOrder;
}

void PmergeMe::insertLosersIntoWinnersVect(std::vector<std::vector<int> >& winner, const std::vector<std::vector<int> >& looser, size_t sizeElem){
	std::vector<size_t> insertionOrder = generateJacobsthalOrderVect(looser.size());
	
	// Insert in Jacobsthal order
	for (size_t i = 0; i < insertionOrder.size(); i++){
		size_t index = insertionOrder[i];
		int needle = 0;
		if (index < _vector.size() && _vector[index].size() >= 2 * sizeElem)
			needle = _vector[index][2 * sizeElem - 1];

		int indexWin = -1;
		for (size_t j = 0; j < winner.size(); j++){
			if (sizeElem > 0 && winner[j].size() >= sizeElem && needle == winner[j][sizeElem - 1]) {
				indexWin = static_cast<int>(j);
			}
		}

		size_t nbForSearch = (indexWin == -1) ? 0u : static_cast<size_t>(indexWin + 1);
		size_t indexInsert = binarySearchVect(winner, looser[index][(sizeElem == 0 ? 0 : sizeElem - 1)], nbForSearch);
		if (indexInsert > winner.size())
			indexInsert = winner.size();
		winner.insert(winner.begin() + indexInsert, looser[index]);
	}
}

void PmergeMe::insertOddVectorBack(std::vector<std::vector<int> >& winner, const std::vector<int>& oddElement, size_t sizeElem){
	(void)sizeElem;
	if (oddElement.empty())
		return;
	int key = oddElement.back();
	size_t indexInsert = binarySearchVect(winner, key, winner.size());
	if (indexInsert > winner.size())
		indexInsert = winner.size();
	winner.insert(winner.begin() + indexInsert, oddElement);
}

void PmergeMe::rebuildVector(const std::vector<std::vector<int> >& winner){
	_vector.clear();
	for (size_t i = 0; i < winner.size(); i++) {
		std::vector<int> tmp;
		for (size_t j = 0; j < winner[i].size(); j++) {
			tmp.push_back(winner[i][j]);
		}
		_vector.push_back(tmp);
	}
}


//===========DEQUE===========
std::deque<int> dequeiser(int nb){
	std::deque<int> deq;
	deq.push_back(nb);
	return (deq);
}

std::deque<int> PmergeMe::handleOddDeque(){
	std::deque<int> oddElement;
	if (_deque.empty())
		return oddElement;

	size_t lastElem = _deque.size() - 1;
    
	if (lastElem % 2 == 0 && lastElem != 0){
		oddElement = _deque[lastElem];
		_deque.pop_back();
	}
    
	return (oddElement);
}

void PmergeMe::doPairingDeque(){
	bool hasPaired = false;
	
	for (size_t i = 0; i < _deque.size(); i += 2){
		if (i + 1 < _deque.size() && _deque[i].size() == _deque[i + 1].size()){
			if (_deque[i][_deque[i].size() - 1] > _deque[i + 1][_deque[i + 1].size() - 1])
				std::swap(_deque[i], _deque[i + 1]);
			_deque[i].insert(_deque[i].end(), _deque[i + 1].begin(), _deque[i + 1].end());
			_deque[i + 1].clear();
			hasPaired = true;
		}
	}
	
	_deque.erase(std::remove_if(_deque.begin(), _deque.end(), isEmptyDeque), _deque.end()); // Delete the empty deques
	
	if (hasPaired && _deque.size() > 1)
		this->sortDeque();
}

void PmergeMe::separateWinnersAndLosersDeq(std::deque<std::deque<int> >& winner, std::deque<std::deque<int> >& looser, size_t sizeElem){
	for (size_t i = 0; i < _deque.size(); i++){
		if (_deque[i].size() == sizeElem * 2) {
			std::deque<int> tmpWin;
			std::deque<int> tmpLoose;

			for (size_t j = 0; j < sizeElem; j++){
				tmpLoose.push_back(_deque[i][j]);
				tmpWin.push_back(_deque[i][j + sizeElem]);
			}
			winner.push_back(tmpWin);
			looser.push_back(tmpLoose);
		}
	}
}

std::deque<size_t> PmergeMe::generateJacobsthalOrderDeq(size_t nbElements){
	std::deque<size_t> insertionOrder;
	
	// Generate the Jacobshtal sequence
	std::deque<size_t> jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	
	size_t maxNeeded = nbElements + 2;
	for (size_t i = 2; i < maxNeeded; i++){
		size_t next = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];
		jacobsthal.push_back(next);
	}
	
	// Create the insertion order with Jacobsthal
	std::deque<bool> inserted(nbElements, false);
	
	for (size_t jacobIndex = 2; jacobIndex < jacobsthal.size(); jacobIndex++){
		size_t currentJacob = jacobsthal[jacobIndex];
		size_t prevJacob = jacobsthal[jacobIndex - 1];
		
		for (size_t pos = std::min(currentJacob, nbElements); pos > prevJacob && pos > 0; pos--){
			size_t index = pos - 1;
			if (index < nbElements && !inserted[index]) {
				insertionOrder.push_back(index);
				inserted[index] = true;
			}
		}
	}
	
	for (size_t i = 0; i < nbElements; i++){
		if (!inserted[i]) {
			insertionOrder.push_back(i);
		}
	}
	return (insertionOrder);
}

size_t	PmergeMe::binarySearchDeq(const std::deque<std::deque<int> >& deq, int elem, size_t nbElem){
	if (nbElem == 0 || deq.empty())
		return 0;

	size_t sizeElem = deq[0].size();
	int left = 0;
	int right = nbElem - 1;
	int mid = 0;

	while (left <= right) {
		mid = left + (right - left) / 2;

		if (deq[mid][sizeElem - 1] < elem)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return (left);
}

void PmergeMe::insertLosersIntoWinnersDeq(std::deque<std::deque<int> >& winner, const std::deque<std::deque<int> >& looser, size_t sizeElem){
	std::deque<size_t> insertionOrder = generateJacobsthalOrderDeq(looser.size());
	
	// Inset in Jacobsthal order
	for (size_t i = 0; i < insertionOrder.size(); i++) {
		size_t index = insertionOrder[i];
		int needle = 0;
		if (index < _deque.size() && _deque[index].size() >= 2 * sizeElem)
			needle = _deque[index][2 * sizeElem - 1];

		int indexWin = -1;
		for (size_t j = 0; j < winner.size(); j++) {
			if (sizeElem > 0 && winner[j].size() >= sizeElem && needle == winner[j][sizeElem - 1]) {
				indexWin = static_cast<int>(j);
			}
		}

		size_t nbForSearch = (indexWin == -1) ? 0u : static_cast<size_t>(indexWin + 1);
		size_t indexInsert = binarySearchDeq(winner, looser[index][(sizeElem == 0 ? 0 : sizeElem - 1)], nbForSearch);
		if (indexInsert > winner.size())
			indexInsert = winner.size();
		winner.insert(winner.begin() + indexInsert, looser[index]);
	}
}

void PmergeMe::insertOddDequeBack(std::vector<std::vector<int> >& winner, const std::vector<int>& oddElement, size_t sizeElem){
	(void)sizeElem;
	if (oddElement.empty())
		return;
	int key = oddElement.back();
	size_t indexInsert = binarySearchVect(winner, key, winner.size());
	if (indexInsert > winner.size())
		indexInsert = winner.size();
	winner.insert(winner.begin() + indexInsert, oddElement);
}

void PmergeMe::insertOddDequeBack(std::deque<std::deque<int> >& winner, const std::deque<int>& oddElement, size_t sizeElem){
	(void)sizeElem;
	if (oddElement.empty())
		return;
	int key = oddElement.back();
	size_t indexInsert = binarySearchDeq(winner, key, winner.size());
	if (indexInsert > winner.size())
		indexInsert = winner.size();
	winner.insert(winner.begin() + indexInsert, oddElement);
}

void PmergeMe::rebuildDeque(const std::deque<std::deque<int> >& winner){
	_deque.clear();
	for (size_t i = 0; i < winner.size(); i++) {
		std::deque<int> tmp;
		for (size_t j = 0; j < winner[i].size(); j++) {
			tmp.push_back(winner[i][j]);
		}
		_deque.push_back(tmp);
	}
}

void PmergeMe::sortDeque(){
	//Step 1: Handle the odd Element if there is one
	std::deque<int> oddElement = handleOddDeque();
	bool hasOdd = !oddElement.empty();
	
	//Step 2: Do the recursive pairing;
	doPairingDeque();
	
	//Step 3: separate the winner and the looser
	std::deque<std::deque<int> > winner;
	std::deque<std::deque<int> > looser;
	if (_deque.empty())
		return;
	size_t sizeElem = _deque[0].size();
    
	if (sizeElem == 1) {
		return; // Sorting is finish
	}
	
	sizeElem /= 2;
	separateWinnersAndLosersDeq(winner, looser, sizeElem);
	
	// Step 4: Use Jacobsthal to insert loosers into winners
	insertLosersIntoWinnersDeq(winner, looser, sizeElem);
	
	// Step 5: Insert the odd element if he exist
	if (hasOdd) {
		insertOddDequeBack(winner, oddElement, sizeElem);
	}
	
	// Step 6: Reconstruct the final vector
	rebuildDeque(winner);
}

//Operators overload
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

std::ostream& operator<<(std::ostream& os, const std::deque<std::deque<int> >& container){
	std::deque<std::deque<int> >::const_iterator it = container.begin();
	std::deque<std::deque<int> >::const_iterator end = container.end();
	
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

// Getters
const std::vector<std::vector<int> >& PmergeMe::getVector() const{
	return _vector;
}

const std::deque<std::deque<int> >& PmergeMe::getDeque() const{
	return _deque;
}