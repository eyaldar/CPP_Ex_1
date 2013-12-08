#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "Point.h"
#include <math.h>
#include <string>

class Square 
{
public:
	Square(const Point& point, unsigned int side_length, char ch)
	: m_top_left(point), m_bottom_right(point.getX() + side_length - 1, point.getY() + side_length - 1), 
	  m_side_length(side_length), m_draw_char(ch) {}

	Square(int x, int y, unsigned int side_length, char ch)
	: m_top_left(x,y), m_bottom_right(x + side_length - 1, y + side_length - 1), 
	  m_side_length(side_length), m_draw_char(ch) {}

	Square(const Square&);

	void setShift(const Point& newShift);
	const Point& getShift() const;

	void move();
	void merge(const Square&);
	void copyFrom(const Square&);

	void draw(bool useMatrix = false) const;
	void draw(char ch, bool useMatrix = false) const;

	void drawAsFilled() const;
	void drawAsFilled(char ch) const;

	bool contains(const Point& point) const;
	bool contains(const Square&) const;
	bool isIntersectingWith(const Square&) const;
	bool isCollidingWith(const Square&) const; 
	bool isCollidingHorizontallyWith(const Square&) const; 
	bool isCollidingVerticallyWith(const Square&) const;
	bool isWithinScreenBounds() const;

	// Compares to squares by area
	// Returns 0 if the areas are equal, in case this square is bigger returns positive number
	// otherwise returns negative number.
	int compareAreaTo(const Square&) const;

	// Compares to squares by horizontal shift
	// Returns 0 if the speeds are equal, in case this square is faster returns positive number
	// otherwise returns negative number.
	int compareHorizontalSpeedTo(const Square&) const;

	// Compares to squares by vertical shift
	// Returns 0 if the speeds are equal, in case this square is faster returns positive number
	// otherwise returns negative number.
	int compareVerticalSpeedTo(const Square&) const;
private:

	unsigned int m_side_length;
	Point m_top_left;
	Point m_bottom_right;
	char m_draw_char;
	Point m_shift;

	void drawToMatrix(char ch) const;
	void drawToScreen(char ch) const;
};

#endif