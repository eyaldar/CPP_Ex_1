#include "Point.h"
#include "Gotoxy.h"

using namespace std;

void Point::draw(char ch) const
{
	if((m_x >= 0 && m_x < 79) &&
	   (m_y >= 0 && m_y < 24))
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