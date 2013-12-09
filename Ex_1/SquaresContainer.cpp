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

Square* SquaresContainer::mergeOnCollision(Square& firstSquare, Square& secondSquare)
{
	Square* selected_square;

	bool isCollidingHorizontally = firstSquare.isCollidingHorizontallyWith(secondSquare);
	bool isCollidingVertically = firstSquare.isCollidingVerticallyWith(secondSquare);
	bool isFirstMovingFasterHorizontally = firstSquare.compareHorizontalSpeedTo(secondSquare) > 0;
	bool isFirstMovingFasterVertically = firstSquare.compareVerticalSpeedTo(secondSquare) > 0;
	bool isSecondAreaBigger = firstSquare.compareAreaTo(secondSquare) < 0;

	if(((isFirstMovingFasterHorizontally && isCollidingHorizontally) ||
		(isFirstMovingFasterVertically && isCollidingVertically)) && isSecondAreaBigger)
	{
		removeSquare(firstSquare);
		selected_square = &secondSquare;
	}
	else
	{
		removeSquare(secondSquare);
		selected_square = &firstSquare;
	}

	if(isCollidingHorizontally)
		selected_square->setShift(Point(selected_square->getShift().getX() * -1, selected_square->getShift().getY()));

	if(isCollidingVertically)
		selected_square->setShift(Point(selected_square->getShift().getX(), selected_square->getShift().getY() * -1));
	
	return selected_square;
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
