#pragma once
#include "BSTNode.h"

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
	//TODO - Representation
	BSTNode* root;
	int lines;
	int cols;

	BSTNode* insert(BSTNode* root, int line, int column, TElem value) const;

	void remove(BSTNode*& root, int i, int j, TElem e);

	BSTNode* search(BSTNode* currentNode, int i, int j) const;
	
	void deleteNode(BSTNode* currentNode);

	BSTNode* getMinimum(BSTNode* node);

	bool relation(BSTNode* node, int i, int j) const;

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	//sets all the values from line to the value elem
	//throws an exception if line is not valid
	void setElemsOnLine(int line, TElem elem);

	~Matrix();
};
