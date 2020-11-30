#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

Bag::Bag() {
	//TODO - Implementation
	this->m = 2;
	this->length = 0;
	this->elements = new TElem[this->m];
	int index;
	for (index = 0; index < this->m; index++)
		this->elements[index] = NULL_TELEM;
}
/*
BC: Theta(capacity)
WC: Theta(capacity)
AC: Theta(capacity)
Total complexity: Theta(capacity)
*/

int Bag::first_hash_function(TElem k) const
{
	return k % this->m;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

int Bag::second_hash_function(TElem k) const
{
	if (k % 2 == 1)
	{
		return 1 + (k + 1) % this->m;
	}
	return 1 + k % this->m;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

int Bag::TFunction(TElem k, int i) const
{
	if (k < 0)
	{
		k = abs(k);
	}
	return (this->first_hash_function(k) + i*this->second_hash_function(k))%this->m;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

void Bag::resizeAndRehash()
{
	int oldCapacity = this->m;
	this->m *= 2;
	
	TElem* newElements = new TElem[this->m];

	this->length = 0;
	for(int index = 0; index < this->m ; index++)
		newElements[index] = NULL_TELEM;

	//rehashing
	for (int index = 0; index < oldCapacity; index++)
	{
		if (this->elements[index] != -111111 && this->elements[index] != -111112)
		{
			int i = 0;
			int currentPosition = this->TFunction(this->elements[index], i);
			while (i < this->m && (newElements[currentPosition] != -111111))
			{
				i++;
				currentPosition = this->TFunction(this->elements[index], i);
			}
			newElements[currentPosition] = this->elements[index];
			this->length++;
		}
	}
	delete[] this->elements;
	this->elements = newElements;
}
/*
BC: Theta(newCapacity)
WC: Theta(newCapacity * oldCapacity)
AC: Theta(newCapacity * oldCapacity)
Total complexity: O(newCapacity * oldCapacity)
*/


void Bag::add(TElem elem) {
	//TODO - Implementation
	int i = 0;
	int currentPosition = this->TFunction(elem, i);
	while (i < this->m && (this->elements[currentPosition] != -111111 && this->elements[currentPosition] != -111112))
	{
		i++;
		currentPosition = this->TFunction(elem, i);
	}
	if (i == this->m)
	{
		this->resizeAndRehash();
		this->add(elem);
	}
	else
	{
		this->elements[currentPosition] = elem;
		this->length++;
	}
}
/*
BC: Theta(1)
WC: Theta(newCapacity * oldCapacity)
AC: Theta(newCapacity * oldCapacity)
Total complexity: O(newCapacity * oldCapacity)
*/


bool Bag::remove(TElem elem) {
	//TODO - Implementation
	int i = 0;
	int currentPosition = this->TFunction(elem, i);
	while (i < this->m && (this->elements[currentPosition] != elem && this->elements[currentPosition] != -111111))
	{
		i++;
		currentPosition = this->TFunction(elem, i);
	}
	if (i == this->m || this->elements[currentPosition] == -111111)
		return false;
	else
	{
		this->length--;
		this->elements[currentPosition] = DELETED;
		return true;
	}
}
/*
BC: Theta(1)
WC: Theta(capacity)
AC: Theta(capacity)
Total complexity: O(capacity)
*/


bool Bag::search(TElem elem) const {
	int i = 0;
	int currentPosition = this->TFunction(elem, i);
	if (this->length == 0)
		return false;
	while (i < this->m && (this->elements[currentPosition] != elem && this->elements[currentPosition] != -111111))
	{
		i++;
		currentPosition = this->TFunction(elem, i);
	}
	if (i == this->m || this->elements[currentPosition] == -111111)
		return false;
	else
		return true;
}
/*
BC: Theta(1)
WC: Theta(capacity)
AC: Theta(capacity)
Total complexity: O(capacity)
*/

int Bag::nrOccurrences(TElem elem) const {
	//TODO - Implementation
	int numberOccurrences = 0;
	int i = 0;
	int currentPosition = this->TFunction(elem, i);
	while (i < this->m && this->elements[currentPosition] != -111111)
	{
		if (this->elements[currentPosition] == elem)
			numberOccurrences++;
		i++;
		currentPosition = this->TFunction(elem, i);
	}
	return numberOccurrences;
}
/*
BC: Theta(1)
WC: Theta(capacity)
AC: Theta(capacity)
Total complexity: O(capacity)
*/


int Bag::size() const {
	//TODO - Implementation
	return this->length;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/


bool Bag::isEmpty() const {
	//TODO - Implementation
	return (this->length == 0);
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

void Bag::empty()
{
	BagIterator iterator = this->iterator();
	while (iterator.valid())
	{
		TElem currentElement = iterator.getCurrent();
		this->remove(currentElement);
		iterator.next();
	}
}
/*
BC: Theta(length)
WC: Theta(length)
AC: Theta(length)
Total complexity: Theta(length)
*/


BagIterator Bag::iterator() const {
	return BagIterator(*this);
}
/*
BC: Theta(1)
WC: Theta(capacity)
AC: Theta(capacity)
Total complexity: O(capacity)
*/


Bag::~Bag() {
	//TODO - Implementation
	delete[] this->elements;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

