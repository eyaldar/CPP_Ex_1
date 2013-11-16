#include "Square.h"
#include "Gotoxy.h"

#include <math.h>
#include <string>
using namespace std;

Square::Square(const Square& other)
{
	copyFrom(other);
}

void Square::draw() const
{
	draw(m_draw_char);
}

void Square::draw(char ch) const
{
	int left = m_top_left.getX();
	int top = m_top_left.getY();
	int right = m_bottom_right.getX();
	int bottom = m_bottom_right.getY();
	Point p;

	for (unsigned int lengthIndex = 0; lengthIndex < m_side_length; lengthIndex++)
	{
		// top side
		p.init(left + lengthIndex, top);
		p.draw(ch);

		// left side
		p.init(left, top + lengthIndex);
		p.draw(ch);

		// bottom side
		p.init(left + lengthIndex, bottom);
		p.draw(ch);

		// right side
		p.init(right, top + lengthIndex);
		p.draw(ch);
	}

	p.init(right, bottom);
	p.draw(ch);
}

bool Square::contains(const Point& point) const
{
	return (m_top_left.getX() <= point.getX() && point.getX() <= m_bottom_right.getX()) &&
		   (m_top_left.getY() <= point.getY() && point.getY() <= m_bottom_right.getY());
}

bool Square::contains(const Square& other) const
{
	return this->contains(other.m_bottom_right) &&
		   this->contains(other.m_top_left);
}

void Square::merge(const Square& other)
{
	bool areIntersecting = this->isIntersectingWith(other);
	bool isThisAreaBigger = this->compareAreaTo(other) > 0;
	bool doesOtherContainsThis = this->contains(other);

	if(!this->contains(other) &&
	   (other.contains(*this) ||
	   (areIntersecting && isThisAreaBigger)  ||
	   (!areIntersecting && !isThisAreaBigger)))
	{
		copyFrom(other);
	}
}

void Square::copyFrom(const Square& other)
{
	this->m_draw_char = other.m_draw_char;
	this->m_side_length = other.m_side_length;
	this->m_top_left = Point(other.m_top_left);
	this->m_bottom_right = Point(other.m_bottom_right);
}

int Square::compareAreaTo(const Square& other) const
{
	int thisArea = this->m_side_length*this->m_side_length;
	int otherArea = other.m_side_length*other.m_side_length;
		
	return thisArea - otherArea;
}

bool Square::isIntersectingWith(const Square& other) const
{
	return  this->m_top_left.getX() <= other.m_bottom_right.getX() &&
			other.m_top_left.getX() <= this->m_bottom_right.getX() &&
			this->m_top_left.getY() <= other.m_bottom_right.getY() &&
			other.m_top_left.getY() <= this->m_bottom_right.getY();
}