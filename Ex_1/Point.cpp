#include "Point.h"
#include "Gotoxy.h"

using namespace std;

void Point::draw(char ch)
{
	if((m_x >= 0 && m_x <= 79) &&
	   (m_y >= 0 && m_y <= 24))
	{
		gotoxy(m_x, m_y);
		cout << ch;
	}
}

void Point::init(int x, int y)
{
	setX(x);
	setY(y);
}

void Point::setX(int x)
{
	m_x = x;
}

int Point::getX()
{
	return m_x;
}

void Point::setY(int y)
{
	m_y = y;
}

int Point::getY()
{
	return m_y;
}