#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	//TODO - Implementation
	this->currentNode = m.head;
}
//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
//Total complexity: Theta(1)


void SortedSetIterator::first() {
	//TODO - Implementation
	this->currentNode = this->multime.head;
}
//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
//Total complexity: Theta(1)


void SortedSetIterator::next() {
	//TODO - Implementation
	if (this->currentNode != nullptr)
		this->currentNode = this->currentNode->getNext();
	else
		throw exception();
}
//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
//Total complexity: Theta(1)

TElem SortedSetIterator::getCurrent()
{
	//TODO - Implementation
	if (this->currentNode != nullptr)
		return this->currentNode->getElement();
	else
		throw exception();
}
//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
//Total complexity: Theta(1)

bool SortedSetIterator::valid() const {
	//TODO - Implementation
	if (this->currentNode == nullptr)
		return false;
	else
		return true;
}
//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
//Total complexity: Theta(1)

