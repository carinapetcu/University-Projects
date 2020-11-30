#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	//TODO - Implementation
	this->currentPosition = 0;
	while (this->currentPosition < this->bag.m && (this->bag.elements[this->currentPosition] == -111111 || this->bag.elements[this->currentPosition] == -111112))
		this->currentPosition++;
}
/*
BC: Theta(1)
WC: Theta(capacity)
AC: Theta(capacity)
Total complexity: O(capacity)
*/

void BagIterator::first() {
	//TODO - Implementation
	this->currentPosition = 0;
	while (this->currentPosition < this->bag.m && (this->bag.elements[this->currentPosition] == -111111 || this->bag.elements[this->currentPosition] == -111112))
		this->currentPosition++;
}
/*
BC: Theta(1)
WC: Theta(capacity)
AC: Theta(capacity)
Total complexity: O(capacity)
*/


void BagIterator::next() {
	//TODO - Implementation
	if (this->currentPosition >= this->bag.m)
		throw exception();
	this->currentPosition++;
	while (this->currentPosition < this->bag.m && (this->bag.elements[this->currentPosition] == -111111 || this->bag.elements[this->currentPosition] == -111112))
		this->currentPosition++;
}
/*
BC: Theta(1)
WC: Theta(capacity)
AC: Theta(capacity)
Total complexity: O(capacity)
*/


bool BagIterator::valid() const {
	//TODO - Implementation
	return (this->currentPosition < this->bag.m);
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/



TElem BagIterator::getCurrent() const
{
	//TODO - Implementation
	if (this->currentPosition >= this->bag.m)
		throw exception();
	return this->bag.elements[this->currentPosition];
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/
