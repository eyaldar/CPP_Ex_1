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

void SquaresContainer::addSquare(int x, int y, unsigned int side_length, char ch)
{
	Square* newSquare = new Square(x, y, side_length, ch);
	m_squares.push_back(newSquare);
}

void SquaresContainer::removeSquare(Square* square)
{
	m_squares.remove(square);
	delete square;
}

void SquaresContainer::drawSquares() const
{
	for (list<Square*>::const_iterator it = m_squares.begin(); it != m_squares.end(); ++it)
	{
		(*it)->draw();
	}
}

void SquaresContainer::promoteSquare(Square* square)
{
	m_squares.remove(square);
	m_squares.push_back(square);
}

void SquaresContainer::mergeSquares(Square* firstSquare, Square* secondSquare)
{
	firstSquare->merge(*secondSquare);
	removeSquare(secondSquare);
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
