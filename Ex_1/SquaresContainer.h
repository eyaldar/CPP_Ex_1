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
private:
	static const int MAX_AVAILABLE_SQUARES = 10;

	int m_numOfSquares;
	Square** m_squares;

	void destruct();
	void reorderSquaresFrom(int emptyIndex, int numOfSquares);
};

#endif