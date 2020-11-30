#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
	//TODO - Implementation
	this->capacity = 10;
	this->slla = new TElem[this->capacity + 1];
	this->next = new int[this->capacity + 1];
	this->head = -1;
	this->firstEmpty = 1;
	this->length = 0;
	int index;
	for (index = 1; index <= this->capacity - 1; index++)
		this->next[index] = index + 1;
	this->next[this->capacity] = -1;
}
/*
BC: Theta(capacity)
WC: Theta(capacity)
AC: Theta(capacity)
Total complexity: Theta(capacity)
*/

void MultiMap::resize() {
	this->firstEmpty = this->capacity + 1;
	this->capacity *= 2;
	TElem* newSLLA = new TElem[this->capacity + 1];
	int* newNext = new int[this->capacity + 1];

	int index;
	for (index = 1; index <= this->length; index++)
	{
		newSLLA[index] = this->slla[index];
		newNext[index] = this->next[index];
	}
		
	for (index = this->length + 1; index <= this->capacity - 1; index++)
		newNext[index] = index + 1;
	newNext[this->capacity] = -1;
	delete[] this->slla;
	delete[] this->next;
	this->slla = newSLLA;
	this->next = newNext;
}
/*
BC: Theta(capacity*2)
WC: Theta(capacity*2)
AC: Theta(capacity*2)
Total complexity: Theta(capacity*2)
*/


void MultiMap::add(TKey c, TValue v) {
	TElem element;
	element.first = c;
	element.second = v;
	if (this->firstEmpty == -1)
		this->resize();
	int occupiedPosition = this->firstEmpty;
	this->firstEmpty = this->next[this->firstEmpty];
	this->slla[occupiedPosition] = element;
	this->next[occupiedPosition] = this->head;
	this->head = occupiedPosition;
	this->length++;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/


bool MultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
	int current = this->head;
	TElem element;
	element.first = c;
	element.second = v;
	int previous = -1;
	while (current != -1 && this->slla[current] != element)
	{
		previous = current;
		current = this->next[current];
	}
	if (current != -1)
	{
		if (current == this->head)
		{
			this->head = this->next[this->head];
		}
		else
		{
			this->next[previous] = this->next[current];
		}
		this->next[current] = this->firstEmpty;
		this->firstEmpty = current;
		this->length--;
		return true;
	}
	else
		return false;
}
/*
BC: Theta(1)
WC: Theta(length)
AC: Theta(length)
Total complexity: O(length)
*/


vector<TValue> MultiMap::search(TKey c) const {
	//TODO - Implementation
	vector<TValue> vectorOfValues;
	int current = this->head;
	while (current != -1)
	{
		if (this->slla[current].first == c)
			vectorOfValues.push_back(this->slla[current].second);
		current = this->next[current];
	}
	return vectorOfValues;
}
/*
BC: Theta(1)
WC: Theta(length)
AC: Theta(length)
Total complexity: O(length)
*/


int MultiMap::size() const {
	//TODO - Implementation
	return this->length;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/


bool MultiMap::isEmpty() const {
	//TODO - Implementation
	if (this->length == 0)
		return true;
	else
		return false;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/


vector<TKey> MultiMap::keySet() const
{
	vector<TKey> keys{};
	MultiMapIterator iterator = this->iterator();
	while (iterator.valid())
	{
		TElem current = iterator.getCurrent();
		if (find(keys.begin(), keys.end(), current.first) == keys.end())
			keys.push_back(current.first);
		iterator.next();
	}
	return keys;
}
/*
BC: Theta(length)
WC: Theta(length)
AC: Theta(length)
Total complexity: Theta(length)
*/


MultiMap::~MultiMap() {
	//TODO - Implementation
	delete[] this->slla;
	delete[] this->next;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

