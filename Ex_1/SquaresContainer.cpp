#include "SquaresContainer.h"

using namespace std;

SquaresContainer::SquaresContainer()
: m_numOfSquares(0), m_squares(NULL) 
{
	init();		
}

SquaresContainer::~SquaresContainer()
{
	destruct();
}

void SquaresContainer::init()
{
	destruct();

	m_numOfSquares = 0;
	m_squares = new Square*[MAX_AVAILABLE_SQUARES];

	for (int squareIndex = 0; squareIndex < m_numOfSquares; squareIndex++)
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

void SquaresContainer::reorderSquaresFrom(int emptyIndex, int numOfSquares)
{
	for (int squareIndex = emptyIndex; squareIndex < numOfSquares; squareIndex++)
	{
		m_squares[squareIndex] = m_squares[squareIndex + 1];
	}

	m_squares[numOfSquares + 1] = NULL;
}

void SquaresContainer::addSquare(int x, int y, unsigned int side_length, char ch)
{
	if(m_numOfSquares < MAX_AVAILABLE_SQUARES)
	{
		m_squares[m_numOfSquares++] = new Square(x, y, side_length, ch);
	}
}

void SquaresContainer::removeSquare(int squareIndex)
{
	if(m_numOfSquares >= squareIndex)
	{
		delete m_squares[squareIndex];
		m_squares[squareIndex] = NULL;

		m_numOfSquares--;

		reorderSquaresFrom(squareIndex, m_numOfSquares);
	}
}

void SquaresContainer::drawSquares()
{
	for (int squareIndex = 0; squareIndex < m_numOfSquares; squareIndex++)
	{
		m_squares[squareIndex]->draw();
	}
}
