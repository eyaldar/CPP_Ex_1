#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "Point.h"

class Square 
{
public:
	Square(Point& point, unsigned int side_length, char ch)
	: m_top_left(point), m_bottom_right(point.getX() + side_length - 1, point.getX() + side_length - 1), 
	  m_side_length(side_length), m_draw_char(ch)
	{
		validateChar(ch);
	}

	Square(int x, int y, unsigned int side_length, char ch)
	: m_top_left(x,y), m_bottom_right(x + side_length - 1, y + side_length - 1), 
	  m_side_length(side_length), m_draw_char(ch) 
	{
		validateChar(ch);
	}

	explicit Square(const Square&);

	void intersect(const Square&);

	void draw() const;
	void drawWithChar(char ch) const;
	bool contains(const Point& point) const;

	// Compares to squares by area
	// Returns 0 if the areas are equal, in case this square is bigger returns positive number
	// otherwise returns negative number.
	int compareAreaTo(const Square&) const;
	bool isIntersecting(const Square&) const;
	bool isContained(const Square&) const;

private:
	unsigned int m_side_length;
	Point m_top_left;
	Point m_bottom_right;
	char m_draw_char;

	bool isValidChar(char);
	void validateChar(char);
	void copyFrom(const Square&);
};

#endif