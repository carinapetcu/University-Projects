#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
	//TODO - Implementation
	this->head = nullptr;
	this->length = 0;
	this->relation = r;
}
//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
//Total complexity: Theta(1)


bool SortedSet::add(TComp elem) {
	//TODO - Implementation
	SLLNode* currentNode = new SLLNode(elem);
	if (head == nullptr)
	{
		this->head = currentNode;
		this->length++;
		return true;
	}
	else
	{
		if (this->search(elem) == true)
			return false;
		if (this->relation(elem, this->head->getElement()))
		{
				currentNode->setNext(this->head);
				this->head = currentNode;
				this->length++;
				return true;
		}
		else
		{
			SLLNode* node = this->head;
			while (node->getNext() != nullptr && this->relation(elem, node->getNext()->getElement()) == false)
			{
				node = node->getNext();
			}
				currentNode->setNext(node->getNext());
				node->setNext(currentNode);
				this->length++;
				return true;
		}
	}
	return false;
}
//BC: Theta(1)
//WC: Theta(lengthOfSLL)
//AC: Theta(lengthOfSLL)
//Total complexity: O(lengthOfSLL)


bool SortedSet::remove(TComp elem) {
	//TODO - Implementation
	if(this->search(elem) == false)
		return false;
	else
	{
		SLLNode* currentNode = this->head;
		SLLNode* previousNode = nullptr;
		while (currentNode != nullptr && currentNode->getElement() != elem)
		{
			previousNode = currentNode;
			currentNode = currentNode->getNext();
		}
		if (currentNode != nullptr && previousNode == nullptr)
		{
			this->head = this->head->getNext();
		}
		else
			if (currentNode != nullptr)
			{
				previousNode->setNext(currentNode->getNext());
				currentNode->setNext(nullptr);
			}
		delete currentNode;
		this->length--;
		return true;
	}
}
//BC: Theta(1)
//WC: Theta(lengthOfSLL)
//AC: Theta(lengthOfSLL)
//Total complexity: O(lengthOfSLL)


bool SortedSet::search(TComp elem) const {
	//TODO - Implementation
	if (this->head != nullptr)
	{
		SLLNode* current = this->head;
		while (current != nullptr && current->getElement() != elem)
		{
			current = current->getNext();
		}
		if (current == nullptr)
			return false;
		else
			return true;
	}
	else
		return false;
}
//BC: Theta(1)
//WC: Theta(lengthOfSLL)
//AC: Theta(lengthOfSLL)
//Total complexity: O(lengthOfSLL)


int SortedSet::size() const {
	//TODO - Implementation
	return this->length;
}
//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
//Total complexity: Theta(1)



bool SortedSet::isEmpty() const {
	//TODO - Implementation
	if (this->head != nullptr)
		return false;
	else
		return true;
}
//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
//Total complexity: Theta(1)

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}
//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
//Total complexity: Theta(1)

void SortedSet::empty()
{
	SLLNode* prevNode = nullptr;
	while (this->head != nullptr)
	{
		prevNode = this->head;
		this->head = this->head->getNext();
		this->length--;
		delete prevNode;
	}
}
/*
BC: Theta(legthOfSLL)
WC: Theta(lengthOfSLL)
AC: Theta(lengthOfSLL)
Total complexity: Theta(lengthOfSLL)
*/


SortedSet::~SortedSet() {
	//TODO - Implementation
	SLLNode* prevNode = nullptr;
	SLLNode* currentNode = this->head;
	while (currentNode != nullptr)
	{
		prevNode = currentNode;
		currentNode = currentNode->getNext();
		delete prevNode;
	}
}
//BC: Theta(lengthOfSLL)
//WC: Theta(lengthOfSLL)
//AC: Theta(lengthOfSLL)
//Total complexity: Theta(lengthOfSLL)


