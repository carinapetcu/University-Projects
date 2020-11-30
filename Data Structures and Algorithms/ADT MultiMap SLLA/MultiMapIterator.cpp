#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <iostream>


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	//TODO - Implementation
	this->current = this->col.head;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

TElem MultiMapIterator::getCurrent() const{
	//TODO - Implementation
	if (this->current == -1)
		throw exception();
	if (this->current <= this->col.length)
		return this->col.slla[this->current];
	else
		return NULL_TELEM;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

bool MultiMapIterator::valid() const {
	//TODO - Implementation
	if (this->current == -1)
		return false;
	else
		return true;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

void MultiMapIterator::next() {
	//TODO - Implementation
	if (this->current == -1)
		throw exception();
	this->current = this->col.next[this->current];
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

void MultiMapIterator::first() {
	//TODO - Implementation
	this->current = this->col.head;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

