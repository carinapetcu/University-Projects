#include "SLLNode.h"

SLLNode::SLLNode(TElem element, SLLNode* next): element(element), next(next) {};

TElem SLLNode::getElement() const
{
	return this->element;
}
//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
//Total complexity: Theta(1)

void SLLNode::setElement(TElem newElement)
{
	this->element = newElement;
}
//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
//Total complexity: Theta(1)

SLLNode* SLLNode::getNext() const
{
	return this->next;
}
//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
//Total complexity: Theta(1)

void SLLNode::setNext(SLLNode* newNext)
{
	this->next = newNext;
}
//BC: Theta(1)
//WC: Theta(1)
//AC: Theta(1)
//Total complexity: Theta(1)