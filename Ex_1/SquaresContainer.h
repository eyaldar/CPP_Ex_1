#ifndef __SQUARES_CONTAINER_H__
#define __SQUARES_CONTAINER_H__

#include "Square.h"
#include <iostream>

class SquaresContainer {
public:
	SquaresContainer() 
	: m_numOfSquares(0), m_squares(NULL), m_containerSize(0) {}

	~SquaresContainer();

	void init(int containerSize);
	void addSquare(int x, int y, unsigned int side_length, char ch); 
	void removeSquare(int);
	void promoteSquare(int squareIndex);
	void intersectSquares(int firstIndex, int secondIndex);

	void drawSquares() const;
	void drawSquaresWithSelection(int squareIndex) const;
	int findSquareByCoordinates(const Point&) const;
	int getNumOfSquares() const;

private:
	static const char SELECTION_CHAR = '@';

	int m_containerSize;
	int m_numOfSquares;
	Square** m_squares;

	void destruct();
	void reorderSquaresFrom(int emptyIndex);
	void selectSquare(int selectedIndex) const;
	void squareIndexNotOutOfBounds(int squareIndex) const;
};

#endif