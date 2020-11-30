#include "Matrix.h"
#include <exception>
#include <iostream>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	   
	//TODO - Implementation
	this->root = nullptr;
	this->lines = nrLines;
	this->cols = nrCols;
}
/*
	BC: Theta(1)
	AC: Theta(1)
	WC: Theta(1)
	Total complexity: Theta(1)
	*/


int Matrix::nrLines() const {
	//TODO - Implementation
	return this->lines;
}
/*
	BC: Theta(1)
	AC: Theta(1)
	WC: Theta(1)
	Total complexity: Theta(1)
	*/


int Matrix::nrColumns() const {
	//TODO - Implementation
	return this->cols;
}
/*
	BC: Theta(1)
	AC: Theta(1)
	WC: Theta(1)
	Total complexity: Theta(1)
	*/


TElem Matrix::element(int i, int j) const {
	//TODO - Implementation
	if ((i < 0 || i >= this->lines) || (j < 0 || j >= this->cols))
		throw exception();
	if (this->root == nullptr)
		return NULL_TELEM;
	BSTNode* result = this->search(this->root, i, j);
	if ( result == nullptr)
		return NULL_TELEM;
	else
		return result->getValue();
}
/*
	BC: Theta(n)
	AC: O(n)
	WC: Theta(n)
	Total complexity: O(n)
*/

BSTNode* Matrix::insert(BSTNode* root, int line, int column, TElem value) const
{
	if (root == nullptr)
		return new BSTNode{ line, column, value, nullptr, nullptr };
	else {
		if (this->relation(root, line, column))
			root->setLeft(this->insert(root->getLeft(), line, column, value));
		else
			root->setRight(this->insert(root->getRight(), line, column, value));
	}
	return root;
}
/*
	BC: Theta(n)
	AC: O(n)
	WC: Theta(n)
	Total complexity: O(n)
*/

void Matrix::remove(BSTNode*& root, int i, int j, TElem e)
{
	BSTNode* parent = nullptr;
	BSTNode* current = root;
	while (current != nullptr && (current->getLine() != i || current->getColumn() != j || current->getValue() != e)){
		parent = current;
		if (this->relation(current, i, j))
			current = current->getLeft();
		else
			current = current->getRight();
		
	}
	if (current == nullptr)
		return;

	if (current->getLeft() == nullptr && current->getRight() == nullptr) {
		if (current != root) {
			if (parent->getLeft() == current)
				parent->setLeft(nullptr);
			else
				parent->setRight(nullptr);
		}
		else
			root = nullptr;
		delete current;
	}
	else if (current->getLeft() && current->getRight()) {
		BSTNode* successor = this->getMinimum(current->getRight());
		int line = successor->getLine();
		int column = successor->getColumn();
		TElem value = successor->getValue();
		remove(root, successor->getLine(), successor->getColumn(), successor->getValue());
		current->setLine(line);
		current->setColumn(column);
		current->setValue(value);
	}
	else {
		BSTNode* child = (current->getLeft()) ? current->getLeft() : current->getRight();
		if (current != root) {
			if (current = parent->getLeft())
				parent->setLeft(child);
			else
				parent->setRight(child);
		}
		else
			root = child;
		delete current;
	}
}
/*
	BC: Theta(n)
	AC: O(n)
	WC: Theta(n)
	Total complexity: O(n)
*/

BSTNode* Matrix::search(BSTNode* currentNode, int i, int j) const
{
	while (currentNode != nullptr)
	{
		if (currentNode->getLine() == i && currentNode->getColumn() == j)
			return currentNode;
		if (this->relation(currentNode, i, j))
			currentNode = currentNode->getLeft();
		else
			currentNode = currentNode->getRight();
	}
	return nullptr;
}
/*
	BC: Theta(1)
	AC: O(n)
	WC: Theta(n)
	Total complexity: O(n)
*/

TElem Matrix::modify(int i, int j, TElem e) {
	//TODO - Implementation
	if ((i < 0 || i >= this->lines) || (j < 0 || j >= this->cols))
		throw exception();
	if (this->root == nullptr)
	{
		this->root = new BSTNode(i, j, e, nullptr, nullptr);
		return NULL_TELEM;
	}
	TElem searchElement = this->element(i, j);
	if (searchElement == 0) {
		if (e != 0) {
			this->insert(this->root,i, j, e);
		}	
	}
	else {
		if (e == 0)
		{
			this->remove(this->root, i, j, searchElement);
		}
		else {
				BSTNode* oldState = this->search(this->root, i, j);
				oldState->setValue(e);
			}
			
		}
	return searchElement;
}
/*
	BC: Theta(n)
	AC: O(n)
	WC: Theta(n)
	Total complexity: O(n)
*/

void Matrix::deleteNode(BSTNode* currentNode)
{
	if(currentNode != nullptr) {
		deleteNode(currentNode->getLeft());
		deleteNode(currentNode->getRight());
		delete currentNode;
	}
}
/*
	BC: Theta(n)
	AC: Theta(n)
	WC: Theta(n)
	Total complexity: Theta(n)
*/

BSTNode* Matrix::getMinimum(BSTNode* node)
{
	while (node->getLeft() != nullptr)
		node = node->getLeft();
	return node;
}
/*
	BC: Theta(n)
	AC: O(n)
	WC: Theta(n)
	Total complexity: O(n)
*/

bool Matrix::relation(BSTNode* node, int i, int j) const
{
	if (node->getLine() == (i - 1) && j == 0 && node->getColumn() == (this->cols - 1))
		return true;
	else if (node->getLine() == i && node->getColumn() <= j)
		return true;
	else if (node->getLine() < i)
		return true;
	return false;
}
/*
	BC: Theta(1)
	AC: Theta(1)
	WC: Theta(1)
	Total complexity: Theta(1)
*/

void Matrix::setElemsOnLine(int line, TElem elem)
{
	if (line < 0 || line >= this->lines)
		throw exception();
	int index;
	for (index = 0; index < this->cols; index++) {
		BSTNode* currentElement = this->search(this->root, line, index);
		if (currentElement != nullptr)
			currentElement->setValue(elem);
		else
			this->insert(this->root, line, index, elem);
	}
}
/*
	BC: Theta(cols)
	AC: O(n*cols)
	WC: Theta(n*cols)
	Total complexity: O(n*cols)
*/


Matrix::~Matrix()
{
	this->deleteNode(this->root);
}
/*
	BC: Theta(n)
	AC: Theta(n)
	WC: Theta(n)
	Total complexity: Theta(n)
*/


