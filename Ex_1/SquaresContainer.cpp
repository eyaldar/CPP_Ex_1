#include "SquaresContainer.h"

using namespace std;

SquaresContainer::~SquaresContainer()
{
	destruct();
}

void SquaresContainer::init(int containerSize)
{
	destruct();

	m_container_size = containerSize;
	m_num_of_squares = 0;
	m_squares = new Square*[containerSize];

	for (int squareIndex = 0; squareIndex < m_container_size; squareIndex++)
	{
		m_squares[squareIndex] = NULL;
	}
}

void SquaresContainer::destruct()
{
	for (int squareIndex = 0; squareIndex < m_num_of_squares; squareIndex++)
	{
		delete m_squares[squareIndex];
	}

	delete[] m_squares;

	m_squares = NULL;
	m_num_of_squares = 0;
}

void SquaresContainer::rearrangeSquaresFrom(int emptyIndex)
{
	for (int squareIndex = emptyIndex; squareIndex < m_num_of_squares - 1; squareIndex++)
	{
		m_squares[squareIndex] = m_squares[squareIndex + 1];
	}

	m_squares[m_num_of_squares - 1] = NULL;
}

void SquaresContainer::addSquare(int x, int y, unsigned int side_length, char ch)
{
	if(m_num_of_squares < m_container_size)
	{
		m_squares[m_num_of_squares++] = new Square(x, y, side_length, ch);
	}
}

void SquaresContainer::removeSquare(int squareIndex)
{
	squareIndexNotOutOfBounds(squareIndex);

	delete m_squares[squareIndex];
	m_squares[squareIndex] = NULL;

	rearrangeSquaresFrom(squareIndex);
	
	m_num_of_squares--;
}

void SquaresContainer::drawSquares() const
{
	for (int squareIndex = 0; squareIndex < m_num_of_squares; squareIndex++)
	{
		m_squares[squareIndex]->draw();
	}
}

void SquaresContainer::drawSquare(int squareIndex, char ch) const
{
	squareIndexNotOutOfBounds(squareIndex);

	m_squares[squareIndex]->draw(ch);
}

void SquaresContainer::promoteSquare(int squareIndex)
{
	squareIndexNotOutOfBounds(squareIndex);

	Square* squareToPromote = m_squares[squareIndex];

	rearrangeSquaresFrom(squareIndex);

	m_squares[m_num_of_squares - 1] = squareToPromote;
}

void SquaresContainer::mergeSquares(int firstIndex, int secondIndex)
{
	squareIndexNotOutOfBounds(firstIndex);
	squareIndexNotOutOfBounds(secondIndex);

	m_squares[firstIndex]->merge(*m_squares[secondIndex]);
	removeSquare(secondIndex);
}

int SquaresContainer::findSquare(const Point& coordinates, int formIndex) const
{
	if(formIndex > m_num_of_squares - 1)
		throw "given fromIndex is invalid!";

	for (int squareIndex = formIndex; squareIndex >= 0; squareIndex--)
	{
		if(m_squares[squareIndex]->contains(coordinates))
		{
			return squareIndex;
		}
	}

	return NOT_FOUND;
}

int SquaresContainer::getNumOfSquares() const
{
	return m_num_of_squares;
}

bool SquaresContainer::isContainerFull() const
{
	return m_num_of_squares >= m_container_size;
}

void SquaresContainer::squareIndexNotOutOfBounds(int squareIndex) const
{
	if(m_num_of_squares < squareIndex || squareIndex < 0)
	{
		string error("Given square index: '" + squareIndex);
		error.append("' is out of bounds!");

		throw error;
	}
}
