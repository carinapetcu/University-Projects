#pragma once
#include <tuple>

class BSTNode
{
private:
	int line;
	int column;
	int value;
	BSTNode* left;
	BSTNode* right;

public:
	BSTNode( int newLine, int newColumn, int newValue, BSTNode* newLeft, BSTNode* newRight) : column(newColumn), line(newLine), value(newValue), left(newLeft), right(newRight) {};
	BSTNode(const BSTNode& newNode) { column = newNode.getColumn(); line = newNode.getLine(); value = newNode.getValue(); left = newNode.getLeft(); right = newNode.getRight(); };
	~BSTNode() {};

	int getColumn() const { return this->column; };
	/*
	BC: Theta(1)
	AC: Theta(1)
	WC: Theta(1)
	Total complexity: Theta(1)
	*/
	int getLine() const { return this->line; };
	/*
	BC: Theta(1)
	AC: Theta(1)
	WC: Theta(1)
	Total complexity: Theta(1)
	*/
	int getValue() const { return this->value; };
	/*
	BC: Theta(1)
	AC: Theta(1)
	WC: Theta(1)
	Total complexity: Theta(1)
	*/
	BSTNode* getLeft() const { return this->left; };
	/*
	BC: Theta(1)
	AC: Theta(1)
	WC: Theta(1)
	Total complexity: Theta(1)
	*/
	BSTNode* getRight() const { return this->right; };
	/*
	BC: Theta(1)
	AC: Theta(1)
	WC: Theta(1)
	Total complexity: Theta(1)
	*/

	void setColumn(int newColumn) { this->column = newColumn; };
	/*
	BC: Theta(1)
	AC: Theta(1)
	WC: Theta(1)
	Total complexity: Theta(1)
	*/
	void setLine(int newLine) { this->line = newLine; };
	/*
	BC: Theta(1)
	AC: Theta(1)
	WC: Theta(1)
	Total complexity: Theta(1)
	*/
	void setValue(int newValue) { this->value = newValue; };
	/*
	BC: Theta(1)
	AC: Theta(1)
	WC: Theta(1)
	Total complexity: Theta(1)
	*/
	void setLeft(BSTNode* newLeft) { this->left = newLeft; };
	/*
	BC: Theta(1)
	AC: Theta(1)
	WC: Theta(1)
	Total complexity: Theta(1)
	*/
	void setRight(BSTNode* newRight) { this->right = newRight; };
	/*
	BC: Theta(1)
	AC: Theta(1)
	WC: Theta(1)
	Total complexity: Theta(1)
	*/

};

