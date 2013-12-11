#include "Square.h"

using namespace std;

Square::Square(const Square& other)
{
	copyFrom(other);
}

void Square::draw(bool useMatrix) const
{
	draw(m_draw_char, useMatrix);
}

void Square::draw(char ch, bool useMatrix) const
{
	if(useMatrix)
		drawToMatrix(ch);
	else
		drawToScreen(ch);
}

void Square::drawAsFilled() const
{
	drawAsFilled(m_draw_char);
}

void Square::drawAsFilled(char ch) const
{
	double left = m_top_left.getX();
	double top = m_top_left.getY();

	for (unsigned int rowIndex = 0; rowIndex < m_side_length; rowIndex++)
	{
		for (unsigned int columnIndex = 0; columnIndex < m_side_length; columnIndex++)
		{
			ScreenMatrix::getInstance().updateScreenMatrix(left + columnIndex, top + rowIndex, ch);
		}
	}
}

void Square::drawToMatrix(char ch) const
{
	double left = m_top_left.getX();
	double top = m_top_left.getY();
	double right = m_bottom_right.getX();
	double bottom = m_bottom_right.getY();

	for (unsigned int lengthIndex = 0; lengthIndex < m_side_length; lengthIndex++)
	{
		// top side
		ScreenMatrix::getInstance().updateScreenMatrix(left + lengthIndex, top, ch);

		// left side
		ScreenMatrix::getInstance().updateScreenMatrix(left, top + lengthIndex, ch);

		// bottom side
		ScreenMatrix::getInstance().updateScreenMatrix(left + lengthIndex, bottom, ch);

		// right side
		ScreenMatrix::getInstance().updateScreenMatrix(right, top + lengthIndex, ch);
	}

	ScreenMatrix::getInstance().updateScreenMatrix(right, bottom, ch);
}

void Square::drawToScreen(char ch) const
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

int Square::compareHorizontalSpeedTo(const Square& other) const
{		
	double thisAbsShift = abs(this->m_shift.getX());
	double otherAbsShift = abs(this->m_shift.getX());

	return (int)(thisAbsShift - otherAbsShift);
}

int Square::compareVerticalSpeedTo(const Square& other) const
{		
	double thisAbsShift = abs(this->m_shift.getY());
	double otherAbsShift = abs(this->m_shift.getY());

	return (int)(thisAbsShift - otherAbsShift);
}

bool Square::isIntersectingWith(const Square& other) const
{
	return  (int)this->m_top_left.getX() <= (int)other.m_bottom_right.getX() &&
			(int)other.m_top_left.getX() <= (int)this->m_bottom_right.getX() &&
			(int)this->m_top_left.getY() <= (int)other.m_bottom_right.getY() &&
			(int)other.m_top_left.getY() <= (int)this->m_bottom_right.getY();
}

const Point& Square::getShift() const
{
	return m_shift;
}

void Square::setShift(const Point& point)
{
	m_shift = Point(point);
}

void Square::move()
{
	if(isWithinScreenBounds())
	{
		if(SCREEN_LEFT_BOUNDARY > m_top_left.getX() + m_shift.getX() ||
		   SCREEN_RIGHT_BOUNDARY <= m_bottom_right.getX() + m_shift.getX())
		{
			m_shift.setX(m_shift.getX() * -1);
		}

		if(SCREEN_TOP_BOUNDARY > m_top_left.getY() + m_shift.getY() ||
		   SCREEN_BOTTOM_BOUNDARY <= m_bottom_right.getY() + m_shift.getY())
		{
			m_shift.setY(m_shift.getY() * -1);
		}
	}

	m_top_left += m_shift;
	m_bottom_right += m_shift;
}

bool Square::isCollidingWith(const Square& other) const
{
	return isCollidingHorizontallyWith(other) || isCollidingVerticallyWith(other);
}

bool Square::isCollidingHorizontallyWith(const Square& other) const
{
	return (this->m_top_left.getX() == other.m_bottom_right.getX() || 
			this->m_top_left.getX() == other.m_top_left.getX()	   ||
			this->m_bottom_right.getX() == other.m_top_left.getX() ||
			this->m_bottom_right.getX() == other.m_bottom_right.getX()) 	&&
			this->isIntersectingWith(other); 
}

bool Square::isCollidingVerticallyWith(const Square& other) const
{
	return  (this->m_top_left.getY() == other.m_bottom_right.getY() || 
			this->m_top_left.getY() == other.m_top_left.getY()	   ||
			this->m_bottom_right.getY() == other.m_top_left.getY() ||
			this->m_bottom_right.getY() == other.m_bottom_right.getY()) 	&&
			this->isIntersectingWith(other); 
}

bool Square::isWithinScreenBounds() const
{
	return SCREEN_TOP_BOUNDARY <= m_top_left.getY() && 
		   m_bottom_right.getY() <= SCREEN_BOTTOM_BOUNDARY  &&
		   SCREEN_LEFT_BOUNDARY <= m_top_left.getX() &&
		   m_bottom_right.getX() <= SCREEN_RIGHT_BOUNDARY;
}