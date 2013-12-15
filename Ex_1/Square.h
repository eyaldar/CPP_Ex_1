#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "Point.h"
#include "Shape.h"
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

	virtual void move();

	virtual void input();

	virtual unsigned int getArea() const;

	virtual bool contains(const Point& point) const;
	virtual bool contains(const Shape*) const;
	virtual bool isIntersectingWith(const Shape*) const; 
	virtual bool isCollidingHorizontallyWith(const Shape*) const; 
	virtual bool isCollidingVerticallyWith(const Shape*) const;
	
	virtual double getMinX() const; 
	virtual double getMaxX() const; 
	virtual double getMinY() const; 
	virtual double getMaxY() const; 

	// Multi dispatch methods
	virtual bool contains(const Square* other) const;
	virtual bool isIntersectingWith(const Square*) const;
	virtual bool isCollidingHorizontallyWith(const Square*) const; 
	virtual bool isCollidingVerticallyWith(const Square*) const;

protected:

	virtual void draw(char ch, bool useMatrix = false) const;
	virtual void drawAsFilled(char ch, bool useMatrix) const;

private:

	unsigned int m_side_length;
	Point m_top_left;
	Point m_bottom_right;

	void copyFrom(const Square&);

};

#endif