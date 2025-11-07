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

//Canonical

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

//===========VECTOR===========

//Non-member fonction
std::vector<int> vectoriser(int nb){
	std::vector<int> vect;
	vect.push_back(nb);
	return (vect);
}

bool	isEmptyVector(const std::vector<int>& v){
	return (v.empty());
}

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
	return (left);
}

size_t	jacobsthalGenerator(size_t sizeElem, size_t index){
	std::vector<size_t> jacobSequence(sizeElem);

	if (sizeElem == 0)
		return 0;
	jacobSequence[0] = 0;
	if (sizeElem == 1)
		return (jacobSequence[0]);
	
	jacobSequence[1] = 1;
	for (size_t i = 2 ; i < sizeElem ; i++){
		jacobSequence[i] = jacobSequence[i - 1] + 2 * jacobSequence[i - 2];
	}
	
	// Afficher le contenu du vecteur
	for (size_t i = 0; i < sizeElem; i++)
		if (i < sizeElem - 1) std::cout << " ";
	std::cout << std::endl;
	
	if (index >= sizeElem)
		return 0;
	return (jacobSequence[index]);
}

PmergeMe::~PmergeMe(){}

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
	
	if (sizeElem == 1) {
		return; // Sorting is finish
	}
	
	sizeElem /= 2;
	separateWinnersAndLosersVect(winner, looser, sizeElem);
	
	// Step 4: Use Jacobsthal to insert loosers into winners
	insertLosersIntoWinnersVect(winner, looser, sizeElem);
	
	// Step 5: Insert the odd element if he exist
	if (hasOdd) {
		insertOddElementBack(winner, oddElement, sizeElem);
	}
	
	// Step 6: Reconstruct the final vector
	rebuildVector(winner);
}

std::vector<int> PmergeMe::handleOddVector() {
	std::vector<int> oddElement;
	size_t lastElem = _vector.size() - 1;
	
	if (lastElem % 2 == 0 && lastElem != 0) {
		oddElement = _vector[lastElem];
		_vector.pop_back();
		// std::cout << "Reste: " << oddElement << std::endl;
		// std::cout << "Vector: " << _vector << std::endl;
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
	
	//std::cout << "Pairing: " << _vector << std::endl << std::endl;
	
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
	//std::cout << "Winner: " << winner << std::endl;
	//std::cout << "Looser: " << looser << std::endl;
}

std::vector<size_t> PmergeMe::generateJacobsthalOrderVect(size_t nbElements) {
	std::vector<size_t> insertionOrder;
	
	// Generate the Jacobshtal sequence
	std::vector<size_t> jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	
	size_t maxNeeded = nbElements + 2;
	for (size_t i = 2; i < maxNeeded; i++){
		size_t next = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];
		jacobsthal.push_back(next);
	}
	
	// Create the insertion order with Jacobsthal
	std::vector<bool> inserted(nbElements, false);
	
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
	
	// std::cout << "Ordre d'insertion Jacobsthal: ";
	// for (size_t i = 0; i < insertionOrder.size(); i++) {
	// 	std::cout << insertionOrder[i];
	// 	if (i < insertionOrder.size() - 1) std::cout << " ";
	// }
	std::cout << std::endl;
	
	return insertionOrder;
}

void PmergeMe::insertLosersIntoWinnersVect(std::vector<std::vector<int> >& winner,
										const std::vector<std::vector<int> >& looser,
										size_t sizeElem) {
	std::vector<size_t> insertionOrder = generateJacobsthalOrderVect(looser.size());
	
	// Insérer dans l'ordre Jacobsthal
	for (size_t i = 0; i < insertionOrder.size(); i++) {
		size_t index = insertionOrder[i];
		int needle = _vector[index][2 * sizeElem - 1];
		int indexWin;
		
		for (size_t j = 0; j < winner.size(); j++) {
			if (needle == winner[j][sizeElem - 1]) {
				indexWin = j;
			}
		}

		size_t indexInsert = binarySearch(winner, looser[index][sizeElem - 1], indexWin + 1);
		winner.push_back(looser[index]);
		std::rotate(winner.begin() + indexInsert, winner.end() - 1, winner.end());
		//std::cout << "--- Inséré élément " << index << ": " << winner << " indexWin = " << indexWin << std::endl;
	}
}

void PmergeMe::insertOddElementBack(std::vector<std::vector<int> >& winner,
									const std::vector<int>& oddElement,
									size_t sizeElem) {
	//std::cout << "reste : " << oddElement << std::endl;
	size_t indexInsert = binarySearch(winner, oddElement[sizeElem - 1], winner.size());
	winner.push_back(oddElement);
	std::rotate(winner.begin() + indexInsert, winner.end() - 1, winner.end());
	//std::cout << winner << std::endl;
}

void PmergeMe::rebuildVector(const std::vector<std::vector<int> >& winner) {
	_vector.clear();
	for (size_t i = 0; i < winner.size(); i++) {
		std::vector<int> tmp;
		for (size_t j = 0; j < winner[i].size(); j++) {
			tmp.push_back(winner[i][j]);
		}
		_vector.push_back(tmp);
	}
	
	// std::cout << "Vector: " << _vector << std::endl;
}

//===========DEQUE===========
std::deque<int> dequeiser(int nb){
	std::deque<int> deq;
	deq.push_back(nb);
	return (deq);
}

std::deque<int> PmergeMe::handleOddDeque(){
	std::deque<int> oddElement;
	size_t lastElem = _deque.size() - 1;
	
	if (lastElem % 2 == 0 && lastElem != 0){
		oddElement = _deque[lastElem];
		_vector.pop_back();
		// std::cout << "Reste: " << oddElement << std::endl;
		// std::cout << "Vector: " << _vector << std::endl;
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
	
	_deque.erase(std::remove_if(_deque.begin(), _deque.end(), isEmptyVector), _deque.end()); // Delete the empty vectors
	
	//std::cout << "Pairing: " << _vector << std::endl << std::endl;
	
	if (hasPaired && _deque.size() > 1)
		this->sortVector();
}

void PmergeMe::separateWinnersAndLosersDeq(std::deque<std::deque<int> >& winner, std::deque<std::deque<int> >& looser, size_t sizeElem){
	for (size_t i = 0; i < _deque.size(); i++){
		if (_deque[i].size() == sizeElem * 2) {
			std::deque<int> tmpWin;
			std::deque<int> tmpLoose;

			for (size_t j = 0; j < sizeElem; j++) {
				tmpLoose.push_back(_deque[i][j]);
				tmpWin.push_back(_deque[i][j + sizeElem]);
			}
			winner.push_back(tmpWin);
			looser.push_back(tmpLoose);
		}
	}
	//std::cout << "Winner: " << winner << std::endl;
	//std::cout << "Looser: " << looser << std::endl;
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
	
	// std::cout << "Ordre d'insertion Jacobsthal: ";
	// for (size_t i = 0; i < insertionOrder.size(); i++) {
	// 	std::cout << insertionOrder[i];
	// 	if (i < insertionOrder.size() - 1) std::cout << " ";
	// }
	std::cout << std::endl;
	
	return (insertionOrder);
}

void PmergeMe::insertLosersIntoWinnersDeq(std::deque<std::deque<int> >& winner, const std::deque<std::deque<int> >& looser, size_t sizeElem){
	std::deque<size_t> insertionOrder = generateJacobsthalOrderDeq(looser.size());
	
	// Insérer dans l'ordre Jacobsthal
	for (size_t i = 0; i < insertionOrder.size(); i++) {
		size_t index = insertionOrder[i];
		int needle = _deque[index][2 * sizeElem - 1];
		int indexWin;
		
		for (size_t j = 0; j < winner.size(); j++) {
			if (needle == winner[j][sizeElem - 1]) {
				indexWin = j;
			}
		}

		size_t indexInsert = binarySearch(winner, looser[index][sizeElem - 1], indexWin + 1);
		winner.push_back(looser[index]);
		std::rotate(winner.begin() + indexInsert, winner.end() - 1, winner.end());
		//std::cout << "--- Inséré élément " << index << ": " << winner << " indexWin = " << indexWin << std::endl;
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
	size_t sizeElem = _deque[0].size();
	
	if (sizeElem == 1) {
		return; // Sorting is finish
	}
	
	sizeElem /= 2;
	separateWinnersAndLosersDeq(winner, looser, sizeElem);
	
	// Step 4: Use Jacobsthal to insert loosers into winners
	insertLosersIntoWinnersVect(winner, looser, sizeElem);
	
	// Step 5: Insert the odd element if he exist
	if (hasOdd) {
		insertOddElementBack(winner, oddElement, sizeElem);
	}
	
	// Step 6: Reconstruct the final vector
	rebuildVector(winner);
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

//Getters
std::vector<std::vector<int> > PmergeMe::getVector(){
	return(_vector);
}

std::deque<std::deque<int> > PmergeMe::getDeque(){
	return(_deque);
}