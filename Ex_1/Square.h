#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "Shape.h"
#include "Point.h"
#include <math.h>
#include <string>

class Square : public Shape
{
public:
	Square()
	{
		input();
	}

	Square(const Point& point, unsigned int side_length, char ch)
	: m_top_left(point), m_bottom_right(point.getX() + side_length - 1, point.getY() + side_length - 1), 
	  m_side_length(side_length), Shape(ch) {}

	Square(int x, int y, unsigned int side_length, char ch)
	: m_top_left(x,y), m_bottom_right(x + side_length - 1, y + side_length - 1), 
	  m_side_length(side_length), Shape(ch) {}

	Square(const Square&);

	void setShift(const Point& newShift);
	const Point& getShift() const;

	void move();

	void input();

	unsigned int getArea() const;

	bool contains(const Point& point) const;
	bool contains(const Shape*) const;
	bool isIntersectingWith(const Shape*) const; 
	bool isCollidingHorizontallyWith(const Shape*) const; 
	bool isCollidingVerticallyWith(const Shape*) const;
	bool isWithinScreenBounds() const;
	
	// Multi dispatch methods
	bool contains(const Square* other) const;
	bool isIntersectingWith(const Square*) const;
	bool isCollidingHorizontallyWith(const Square*) const; 
	bool isCollidingVerticallyWith(const Square*) const;
protected:

	void draw(char ch, bool useMatrix = false) const;
	void drawAsFilled(char ch, bool useMatrix) const;

private:

	unsigned int m_side_length;
	Point m_top_left;
	Point m_bottom_right;

	void copyFrom(const Square&);

};

#endif