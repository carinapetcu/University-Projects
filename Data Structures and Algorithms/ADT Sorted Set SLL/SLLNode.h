#pragma once

typedef int TElem;

class SLLNode
{
private:
	TElem element;
	SLLNode* next;

public:
	SLLNode(TElem element = 0, SLLNode* next = nullptr);
	~SLLNode() {};

	TElem getElement() const;
	void setElement(TElem newElement);

	SLLNode* getNext() const;
	void setNext(SLLNode* newNext);
};