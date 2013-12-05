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
	double left = m_top_left.getX();
	double top = m_top_left.getY();
	double right = m_bottom_right.getX();
	double bottom = m_bottom_right.getY();
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
	return  (int)this->m_top_left.getX() <= (int)other.m_bottom_right.getX() &&
			(int)other.m_top_left.getX() <= (int)this->m_bottom_right.getX() &&
			(int)this->m_top_left.getY() <= (int)other.m_bottom_right.getY() &&
			(int)other.m_top_left.getY() <= (int)this->m_bottom_right.getY();
}

void Square::setShift(const Point& point)
{
	m_shift = Point(point);
}

bool Square::move()
{
	Point oldTopLeft = Point(m_top_left);

	m_top_left += m_shift;
	m_bottom_right += m_shift;

	return (oldTopLeft == m_top_left);
}
