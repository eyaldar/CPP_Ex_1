#include "Point.h"

using namespace std;

void Point::draw(char ch) const
{
	if((m_x >= SCREEN_LEFT_BOUNDARY && m_x < SCREEN_RIGHT_BOUNDARY) &&
	   (m_y >= SCREEN_TOP_BOUNDARY && m_y < SCREEN_BOTTOM_BOUNDARY))
	{
		gotoxy((int)m_x, (int)m_y);
		cout << ch;
	}
}

void Point::init(double x, double y)
{
	setX(x);
	setY(y);
}

void Point::setX(double x)
{
	m_x = x;
}

double Point::getX() const
{
	return m_x;
}

void Point::setY(double y)
{
	m_y = y;
}

double Point::getY() const
{
	return m_y;
}

Point& Point::operator+=(const Point& shift)
{
	m_x += shift.m_x;
	m_y += shift.m_y;

	return *this;
}

bool Point::operator==(const Point& other)
{
	return (int)m_x == (int)other.m_x &&
		   (int)m_y == (int)other.m_y;
}

bool Point::operator!=(const Point& other)
{
	return !(*this == other);
}