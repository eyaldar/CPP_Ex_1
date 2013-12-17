#include "Point.h"

using namespace std;

void Point::draw(char ch, bool useMatrix) const
{
	if(ScreenMatrix::getInstance().isWithinScreenBoundaries((int)m_x, (int)m_y))
	{
		if(useMatrix)
		{
			ScreenMatrix::getInstance().updateScreenMatrix((int)m_x, (int)m_y, ch);
		}
		else
		{
			gotoxy((int)m_x, (int)m_y);
			cout << ch;
		}
	}
}

void Point::input()
{
	double x,y;

	cout << "Please enter the X coordinate :";
	cin >> x;
	cout << "Please enter the Y coordinate :";
	cin >> y;

	m_x = (int)x;
	m_y = (int)y;
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

// File operations

void Point::save(ofstream& outFile) const
{
	// Save x
	outFile.write((const char*)&m_x, sizeof(m_x));

	// Save y
	outFile.write((const char*)&m_y, sizeof(m_y));
}

void Point::load(ifstream& inFile)
{
	// Load x
	inFile.read((char*)&m_x, sizeof(m_x));

	// Load y
	inFile.read((char*)&m_y, sizeof(m_y));
}