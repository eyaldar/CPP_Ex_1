#include "SquaresContainer.h"

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

void SquaresContainer::drawSquares()
{
	for (int squareIndex = 0; squareIndex < m_numOfSquares; squareIndex++)
	{
		m_squares[squareIndex]->draw();
	}
}

void SquaresContainer::selectSquare(int selectedIndex)
{
	squareIndexNotOutOfBounds(selectedIndex);

	drawSquares();
	m_squares[selectedIndex]->drawWithChar(SELECTION_CHAR);
}

void SquaresContainer::promoteSquare(int squareIndex)
{
	squareIndexNotOutOfBounds(squareIndex);

	Square* squareToPromote = m_squares[squareIndex];

	reorderSquaresFrom(squareIndex);

	m_squares[m_numOfSquares - 1] = squareToPromote;
}

int SquaresContainer::findSquareByCoordinates(const Point& coordinates)
{
	for (int squareIndex = m_numOfSquares-1; squareIndex >= 0; squareIndex--)
	{
		if(m_squares[squareIndex]->contains(coordinates))
		{
			return squareIndex;
		}
	}

	return -1;
}

void SquaresContainer::selectSquareByCoordinates(int x, int y)
{
	int squareIndex = findSquareByCoordinates(Point(x,y));

	if(squareIndex != -1)
	{
		selectSquare(squareIndex);
	}
	else
	{
		drawSquares();
	}
}

int SquaresContainer::getNumOfSquares()
{
	return m_numOfSquares;
}

void SquaresContainer::squareIndexNotOutOfBounds(int squareIndex)
{
	if(m_numOfSquares < squareIndex || squareIndex < 0)
	{
		throw "Given square index is out of bounds!";
	}
}
