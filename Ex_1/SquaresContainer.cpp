#include "SquaresContainer.h"
#include <string.h>

using namespace std;

SquaresContainer::~SquaresContainer()
{
	destruct();
}

void SquaresContainer::init(int containerSize)
{
	destruct();

	m_containerSize = containerSize;
	m_numOfSquares = 0;
	m_squares = new Square*[containerSize];

	for (int squareIndex = 0; squareIndex < m_containerSize; squareIndex++)
	{
		m_squares[squareIndex] = NULL;
	}
}

void SquaresContainer::destruct()
{
	for (int squareIndex = 0; squareIndex < m_numOfSquares; squareIndex++)
	{
		delete m_squares[squareIndex];
	}

	delete[] m_squares;

	m_squares = NULL;
	m_numOfSquares = 0;
}

void SquaresContainer::reorderSquaresFrom(int emptyIndex)
{
	for (int squareIndex = emptyIndex; squareIndex < m_numOfSquares - 1; squareIndex++)
	{
		m_squares[squareIndex] = m_squares[squareIndex + 1];
	}

	m_squares[m_numOfSquares - 1] = NULL;
}

void SquaresContainer::addSquare(int x, int y, unsigned int side_length, char ch)
{
	if(m_numOfSquares < m_containerSize)
	{
		m_squares[m_numOfSquares++] = new Square(x, y, side_length, ch);
	}
}

void SquaresContainer::removeSquare(int squareIndex)
{
	squareIndexNotOutOfBounds(squareIndex);

	delete m_squares[squareIndex];
	m_squares[squareIndex] = NULL;

	reorderSquaresFrom(squareIndex);
	
	m_numOfSquares--;
}

void SquaresContainer::drawSquares() const
{
	for (int squareIndex = 0; squareIndex < m_numOfSquares; squareIndex++)
	{
		m_squares[squareIndex]->draw();
	}
}

void SquaresContainer::drawSquaresWithSelection(int squareIndex) const
{
	squareIndexNotOutOfBounds(squareIndex);

	drawSquares();
	m_squares[squareIndex]->drawWithChar(SELECTION_CHAR);
}

void SquaresContainer::promoteSquare(int squareIndex)
{
	squareIndexNotOutOfBounds(squareIndex);

	Square* squareToPromote = m_squares[squareIndex];

	reorderSquaresFrom(squareIndex);

	m_squares[m_numOfSquares - 1] = squareToPromote;
}

void SquaresContainer::intersectSquares(int firstIndex, int secondIndex)
{
	squareIndexNotOutOfBounds(firstIndex);
	squareIndexNotOutOfBounds(secondIndex);

	m_squares[firstIndex]->intersect(*m_squares[secondIndex]);
	removeSquare(secondIndex);
}

int SquaresContainer::findSquareByCoordinates(const Point& coordinates) const
{
	for (int squareIndex = m_numOfSquares - 1; squareIndex >= 0; squareIndex--)
	{
		if(m_squares[squareIndex]->contains(coordinates))
		{
			return squareIndex;
		}
	}

	return -1;
}

int SquaresContainer::getNumOfSquares() const
{
	return m_numOfSquares;
}

void SquaresContainer::squareIndexNotOutOfBounds(int squareIndex) const
{
	if(m_numOfSquares < squareIndex || squareIndex < 0)
	{
		string error("Given square index: '" + squareIndex);
		error.append("' is out of bounds!");

		throw error;
	}
}
