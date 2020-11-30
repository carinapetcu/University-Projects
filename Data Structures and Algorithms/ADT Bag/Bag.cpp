#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	//TODO - Implementation
	this->elementsCapacity = 10;
	this->elementsLength = 0;
	this->frequencyCapacity = 10;
	this->frequencyLength = 0;

	this->elements = new TElem[this->elementsCapacity];
	this->frequency = new TElem[this->frequencyCapacity];
}
/*BC: Theta(1)
  WC: Theta(1)
  AC: Theta(1)
  Total time complexity: Theta(1)*/


void Bag::resizeDynamicArray()
{
	this->elementsCapacity *= 2;
	this->frequencyCapacity *= 2;

	int index;
	TElem* newElements = new TElem[this->elementsCapacity];
	for (index = 0; index < this->elementsLength; index++)
		newElements[index] = this->elements[index];
	delete[] this->elements;
	this->elements = newElements;

	TElem* newFrequency = new TElem[this->frequencyCapacity];
	for (index = 0; index < this->frequencyLength; index++)
		newFrequency[index] = this->frequency[index];
	delete[] this->frequency;
	this->frequency = newFrequency;

}
/*BC: Theta(n)
  WC: Theta(n)
  AC: Theta(n)
  Total time complexity: Theta(n)*/

void Bag::add(TElem elem) {
	//TODO - Implementation
	if (this->elementsCapacity == this->elementsLength)
		this->resizeDynamicArray();
	int index;
	for (index = 0; index < this->elementsLength; index++)
		if (this->elements[index] == elem)
		{
			this->frequency[index]++;
			return;
		}
	this->elements[this->elementsLength++] = elem;
	this->frequency[this->frequencyLength++] = 1;
}
//O(n)
/*BC: Theta(1)
  WC: Theta(n)
  AC: Theta(n)
  Total time complexity: O(n)*/


bool Bag::remove(TElem elem) {
	//TODO - Implementation
	int index, position = -1;
	for(index = 0; index < this->elementsLength; index++)
		if (this->elements[index] == elem)
		{
			position = index;
			break;
		}
	if (position == -1)
		return false;
	if (this->frequency[position] > 1)
	{
		this->frequency[position]--;
		return true;
	}
	else
	{
		for (index = position; index < this->elementsLength - 1; index++)
		{
			this->elements[index] = this->elements[index + 1];
			this->frequency[index] = this->frequency[index + 1];
		}
		this->elementsLength--;
		this->frequencyLength--;
		return true;
	}
}
/*BC: Theta(1)
  WC: Theta(n)
  AC: Theta(n)
  Total time complexity: O(n)*/


bool Bag::search(TElem elem) const {
	//TODO - Implementation
	int index;
	for (index = 0; index < this->elementsLength; index++)
		if (this->elements[index] == elem)
			return true;
	return false; 
}
/*BC: Theta(1)
  WC: Theta(n)
  AC: Theta(n)
  Total time complexity: O(n)*/

int Bag::nrOccurrences(TElem elem) const {
	//TODO - Implementation
	int index;
	for (index = 0; index < this->elementsLength; index++)
		if (this->elements[index] == elem)
			return this->frequency[index];
	return 0; 
}
/*BC: Theta(1)
  WC: Theta(n)
  AC: Theta(n)
  Total time complexity: O(n)*/


int Bag::size() const {
	//TODO - Implementation
	int sizeOfBag = 0, index;
	for (index = 0; index < this->frequencyLength; index++)
		sizeOfBag += this->frequency[index];
	return sizeOfBag;
}
/*BC: Theta(n)
  WC: Theta(n)
  AC: Theta(n)
  Total time complexity: Theta(n)*/


bool Bag::isEmpty() const {
	//TODO - Implementation
	if (this->elementsLength == 0)
		return 1;
	return 0;
}
/*BC: Theta(1)
  WC: Theta(1)
  AC: Theta(1)
  Total time complexity: Theta(1)*/

BagIterator Bag::iterator() const {
	//TODO - Implementation
	return BagIterator(*this);
}
/*BC: Theta(1)
  WC: Theta(1)
  AC: Theta(1)
  Total time complexity: Theta(1)*/


Bag::~Bag() {
	//TODO - Implementation
	delete[] this->elements;
	delete[] this->frequency;
}
/*BC: Theta(1)
  WC: Theta(1)
  AC: Theta(1)
  Total time complexity: Theta(1)*/

