#include "Square.h"

using namespace std;

Square::Square(const Square& other)
	: Shape(other.m_draw_char)
{
	copyFrom(other);
}

void Square::draw(char ch, bool useMatrix) const
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
		p.draw(ch, useMatrix);

		// left side
		p.init(left, top + lengthIndex);
		p.draw(ch, useMatrix);

		// bottom side
		p.init(left + lengthIndex, bottom);
		p.draw(ch, useMatrix);

		// right side
		p.init(right, top + lengthIndex);
		p.draw(ch, useMatrix);
	}

	p.init(right, bottom);
	p.draw(ch, useMatrix);
}

void Square::drawAsFilled(char ch, bool useMatrix) const
{
	Point currP;
	int left = (int)m_top_left.getX();
	int top = (int)m_top_left.getY();

	for (unsigned int rowIndex = 0; rowIndex < m_side_length; rowIndex++)
	{
		for (unsigned int columnIndex = 0; columnIndex < m_side_length; columnIndex++)
		{
			currP.init(left + columnIndex, top + rowIndex);
			currP.draw(ch, useMatrix);
		}
	}
}

bool Square::contains(const Point& point) const
{
	return ((int)m_top_left.getX() <= point.getX() && point.getX() <= (int)m_bottom_right.getX()) &&
		   ((int)m_top_left.getY() <= point.getY() && point.getY() <= (int)m_bottom_right.getY());
}

bool Square::contains(const Shape* other) const
{
	return other->contains(this);
}

void Square::copyFrom(const Square& other)
{
	this->m_draw_char = other.m_draw_char;
	this->m_side_length = other.m_side_length;
	this->m_top_left = Point(other.m_top_left);
	this->m_bottom_right = Point(other.m_bottom_right);
}

bool Square::isIntersectingWith(const Shape* other) const
{
	return  other->isIntersectingWith(this);
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

bool Square::isCollidingHorizontallyWith(const Shape* other) const
{
	return other->isCollidingHorizontallyWith(this);
}

bool Square::isCollidingVerticallyWith(const Shape* other) const
{
	return other->isCollidingVerticallyWith(this);
}

unsigned int Square::getArea() const
{
	return m_side_length * m_side_length;
}

void Square::input()
{
	double sideLength;
	char ch;

	m_top_left.input();

	cout << "Please enter the side length [At least 1] :";
	cin >> sideLength;

	while(sideLength < 1)
	{
		cerr << "Invalid side length !." << endl << endl << endl;

		cout << "Please enter the side length [At least 1] :";
		cin >> sideLength;
	}

	m_side_length = (int)sideLength;

	m_bottom_right.init(m_top_left.getX() + m_side_length - 1, m_top_left.getY() + m_side_length - 1);

	cout << "Please enter the square character ['@' is not allowed]:";
	cin >> ch;

	while(ch == m_selection_char)
	{
		cerr << "Invalid character ! Please insert different square character ." << endl << endl << endl;

		cout << "Please enter the square character ['@' is not allowed]:";
		cin >> ch;
	}

	m_draw_char = ch;
}

double Square::getMinX() const
{
	return m_top_left.getX();
}

double Square::getMaxX() const
{
	return m_bottom_right.getX();
}

double Square::getMinY() const
{
	return m_top_left.getY();
}

double Square::getMaxY() const
{
	return m_bottom_right.getY();
}

// Multi Dispatch methods

bool Square::contains(const Square* other) const
{
	return this->contains(other->m_bottom_right) &&
		   this->contains(other->m_top_left);
}

bool Square::isIntersectingWith(const Square* other) const
{
	return  (int)this->m_top_left.getX() <= (int)other->m_bottom_right.getX() &&
			(int)other->m_top_left.getX() <= (int)this->m_bottom_right.getX() &&
			(int)this->m_top_left.getY() <= (int)other->m_bottom_right.getY() &&
			(int)other->m_top_left.getY() <= (int)this->m_bottom_right.getY();
}

bool Square::isCollidingHorizontallyWith(const Square* other) const
{
	return ((int)this->m_top_left.getX() == (int)other->m_bottom_right.getX() || 
			(int)this->m_top_left.getX() == (int)other->m_top_left.getX()	   ||
			(int)this->m_bottom_right.getX() == (int)other->m_top_left.getX() ||
			(int)this->m_bottom_right.getX() == (int)other->m_bottom_right.getX()) 	&&
			this->isIntersectingWith(other); 
}

bool Square::isCollidingVerticallyWith(const Square* other) const
{
	return  ((int)this->m_top_left.getY() == (int)other->m_bottom_right.getY() || 
			(int)this->m_top_left.getY() == (int)other->m_top_left.getY()	   ||
			(int)this->m_bottom_right.getY() == (int)other->m_top_left.getY() ||
			(int)this->m_bottom_right.getY() == (int)other->m_bottom_right.getY()) 	&&
			this->isIntersectingWith(other); 
}