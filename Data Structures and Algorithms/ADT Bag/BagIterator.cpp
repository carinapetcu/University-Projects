  #include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	//TODO - Implementation
	this->currentFrequency = 1;
	this->currentPosition = 0;
}
/*BC: Theta(1)
  WC: Theta(1)
  AC: Theta(1)
  Total time complexity: Theta(1)*/

void BagIterator::first() {
	//TODO - Implementation
	this->currentFrequency = 1;
	this->currentPosition = 0;
}
/*BC: Theta(1)
  WC: Theta(1)
  AC: Theta(1)
  Total time complexity: Theta(1)*/


void BagIterator::next() {
	//TODO - Implementation
	if (this->valid() == false)
		throw exception();
	this->currentFrequency++;
	if (this->bag.nrOccurrences(this->bag.elements[this->currentPosition]) < this->currentFrequency)
	{
		this->currentPosition++;
		this->currentFrequency = 1;
	}
}
/*BC: Theta(1)
  WC: Theta(1)
  AC: Theta(1)
  Total time complexity: Theta(1)*/


bool BagIterator::valid() const {
	//TODO - Implementation
	if (this->currentPosition < this->bag.elementsLength)
		return true;
	return false;
}
/*BC: Theta(1)
  WC: Theta(1)
  AC: Theta(1)
  Total time complexity: Theta(1)*/



TElem BagIterator::getCurrent() const
{
	//TODO - Implementation
	if (this->valid() == false)
		throw exception();
	if (this->currentPosition == this->bag.elementsLength)
		return NULL_TELEM;
	return this->bag.elements[this->currentPosition];
}
/*BC: Theta(1)
  WC: Theta(1)
  AC: Theta(1)
  Total time complexity: Theta(1)*/
