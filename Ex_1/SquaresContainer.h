#ifndef __SQUARES_CONTAINER_H__
#define __SQUARES_CONTAINER_H__

#include "Square.h"
#include <iostream>

class SquaresContainer {
public:
	SquaresContainer();
	~SquaresContainer();

	void init();
	void addSquare(int x, int y, unsigned int side_length, char ch); 
	void removeSquare(int);
	void drawSquares();
	void selectSquareByCoordinates(int x, int y);

	int getNumOfSquares();
private:
	static const int MAX_AVAILABLE_SQUARES = 10;
	static const char SELECTION_CHAR = '@';

	int m_numOfSquares;
	Square** m_squares;

	void destruct();
	void reorderSquaresFrom(int emptyIndex, int numOfSquares);
	void selectSquare(int selectedIndex);
	int findSquareByCoordinates(const Point& coordinates);
};

#endif