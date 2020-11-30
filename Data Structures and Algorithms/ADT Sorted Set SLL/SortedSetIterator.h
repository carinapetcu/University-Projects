#pragma once
#include "SortedSet.h"
#include "SLLNode.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& multime;
	SortedSetIterator(const SortedSet& m);

	//TODO - Representation
	SLLNode* currentNode;

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};

