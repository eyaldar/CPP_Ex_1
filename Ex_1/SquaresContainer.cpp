#include "SquaresContainer.h"

using namespace std;

SquaresContainer::~SquaresContainer()
{
	destruct();
}

void SquaresContainer::init()
{
	destruct();

	m_squares.clear();
}

void SquaresContainer::destruct()
{
	for (list<Square*>::iterator it = m_squares.begin(); it != m_squares.end(); ++it)
	{
		delete *it;
	}

	m_squares.clear();
}

void SquaresContainer::addSquare(const Square& square)
{
	Square* newSquare = new Square(square);
	m_squares.push_back(newSquare);
}

void SquaresContainer::removeSquare(Square& square)
{
	m_squares.remove(&square);
	delete &square;
}

void SquaresContainer::drawSquares() const
{
	for (list<Square*>::const_iterator it = m_squares.begin(); it != m_squares.end(); ++it)
	{
		(*it)->draw();
	}
}

void SquaresContainer::promoteSquare(Square& square)
{
	m_squares.remove(&square);
	m_squares.push_back(&square);
}

void SquaresContainer::mergeSquares(Square& firstSquare, Square& secondSquare)
{
	firstSquare.merge(secondSquare);
	removeSquare(secondSquare);
}

Square* SquaresContainer::collideSquares(Square& firstSquare, Square& secondSquare)
{
	Square* surviver;

	bool isCollidingHorizontally = firstSquare.isCollidingHorizontallyWith(secondSquare);
	bool isCollidingVertically = firstSquare.isCollidingVerticallyWith(secondSquare);
	bool isFirstMovingFasterHorizontally = firstSquare.compareHorizontalSpeedTo(secondSquare) > 0;
	bool isFirstMovingFasterVertically = firstSquare.compareVerticalSpeedTo(secondSquare) > 0;
	bool isSecondAreaBigger = firstSquare.compareAreaTo(secondSquare) < 0;

	if(((isFirstMovingFasterHorizontally && isCollidingHorizontally) ||
		(isFirstMovingFasterVertically && isCollidingVertically)) && isSecondAreaBigger)
	{
		removeSquare(firstSquare);
		surviver = &secondSquare;
	}
	else
	{
		removeSquare(secondSquare);
		surviver = &firstSquare;
	}
	
	return surviver;
}

void SquaresContainer::getSquaresRelations(Square& firstSquare, Square& secondSquare, 
									bool& hasSubsetRelation, bool& hasIntersectionRelation) const
{
		hasIntersectionRelation = firstSquare.isIntersectingWith(secondSquare);
								
		hasSubsetRelation = (firstSquare.contains(secondSquare) ||
							 secondSquare.contains(firstSquare));
}

Square* SquaresContainer::findSquare(const Point& coordinates, const Square* except) const
{
	for (list<Square*>::const_iterator it = m_squares.begin(); it != m_squares.end(); ++it)
	{
		if(*it != except && (*it)->contains(coordinates))
		{
			return *it;
		}
	}

	return NOT_FOUND;
}
