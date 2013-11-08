#ifndef __SQUARES_CONTAINER_H__
#define __SQUARES_CONTAINER_H__

#include "Square.h"
#include <iostream>

class SquaresContainer {
public:
	void init();
	void addSquare(Square& square); 
	void removeSquare(const Square& square);
	void drawSquares();
private:
	static const int MAX_AVAILABLE_SQUARES = 10;

	int m_numOfSquares;
	Square* m_squares;
};

#endif