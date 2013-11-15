#ifndef __SQUARES_CONTAINER_H__
#define __SQUARES_CONTAINER_H__

#include "Square.h"

class SquaresContainer {
public:
	static const char SELECTION_CHAR = '@';
	static const int NOT_FOUND = -1;

	SquaresContainer() 
	: m_num_of_squares(0), m_squares(NULL), m_container_size(0) {}

	~SquaresContainer();

	void init(int containerSize);
	void addSquare(int x, int y, unsigned int side_length, char ch); 
	void removeSquare(int);
	void promoteSquare(int squareIndex);
	void intersectSquares(int firstIndex, int secondIndex);
	
	void drawSquares() const;
	void drawSquaresWithSelection(int squareIndex) const;
	int findSquareByCoordinates(const Point&) const;
	bool isContainerFull() const;

private:	
	int m_container_size;
	int m_num_of_squares;
	Square** m_squares;

	void destruct();
	void reorderSquaresFrom(int emptyIndex);
	void selectSquare(int selectedIndex) const;
	void squareIndexNotOutOfBounds(int squareIndex) const;
};

#endif