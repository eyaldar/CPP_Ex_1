#ifndef __SQUARES_CONTAINER_H__
#define __SQUARES_CONTAINER_H__

#include <list>
#include "Square.h"

#define NOT_FOUND NULL

class SquaresContainer {
public:

	SquaresContainer() 
	{
		init();

		m_squares.resize(10);
	}

	~SquaresContainer();

	void init();
	void addSquare(const Square& square);
	void removeSquare(Square&);
	void promoteSquare(Square&);
	void mergeSquares(Square&, Square&);
	void mergeOnCollision(Square&, Square&);
	
	void drawSquares() const;
	void drawIntersectingWith(const Square& square) const;
	Square* findSquare(const Point& coordinates, const Square* except = NULL) const;
private:	
	std::list<Square*> m_squares;

	void destruct();
};

#endif