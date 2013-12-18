#include "Square.h"

using namespace std;

static const char* TYPE_NAME = "Square";

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

void Square::copyFrom(const Square& other)
{
	Shape::copyFrom(other);

	this->m_side_length = other.m_side_length;
	this->m_top_left = Point(other.m_top_left);

	updateCorners();
	initCornersVector();
}

void Square::initCornersVector()
{
	m_corner_points.clear();

	m_corner_points.push_back(&m_top_left);
	m_corner_points.push_back(&m_top_right);
	m_corner_points.push_back(&m_bottom_left);
	m_corner_points.push_back(&m_bottom_right);
}

void Square::move()
{
	deflectOnBounds();

	m_top_left += m_shift;
	updateCorners();
}

void Square::updateCorners()
{
	double top = m_top_left.getY();
	double left = m_top_left.getX();

	m_top_right.init(left + m_side_length - 1, top);
	m_bottom_left.init(left, top + m_side_length - 1);
	m_bottom_right.init(left + m_side_length - 1, top + m_side_length - 1);
}

bool Square::isCollidingHorizontallyWith(const Shape& other) const
{
	return other.isCollidingHorizontallyWith(*this);
}

bool Square::isCollidingVerticallyWith(const Shape& other) const
{
	return other.isCollidingVerticallyWith(*this);
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

	updateCorners();
	initCornersVector();

		cout << "Please enter the square character ['" << m_selection_char << "' is not allowed]:";
	cin >> ch;

	while(ch == m_selection_char)
	{
		cerr << "Invalid character ! Please insert different square character ." << endl << endl << endl;

		cout << "Please enter the square character ['" << m_selection_char << "' is not allowed]:";
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

// File operations

void Square::save(ofstream& outFile) const
{
	Shape::save(outFile);

	// Save side length
	outFile.write((const char*)&m_side_length, sizeof(m_side_length));

	// Save top left
	m_top_left.save(outFile);
}

void Square::load(ifstream& inFile)
{
	Shape::load(inFile);

	// Save side length
	inFile.read((char*)&m_side_length, sizeof(m_side_length));

	// Save top left
	m_top_left.load(inFile);

	updateCorners();
	initCornersVector();
}

// Multi Dispatch methods

bool Square::isCollidingHorizontallyWith(const Square& other) const
{
	return ((int)this->m_top_left.getX() == (int)other.m_bottom_right.getX() || 
			(int)this->m_top_left.getX() == (int)other.m_top_left.getX()	   ||
			(int)this->m_bottom_right.getX() == (int)other.m_top_left.getX() ||
			(int)this->m_bottom_right.getX() == (int)other.m_bottom_right.getX()) 	&&
			this->isIntersectingWith(other); 
}

bool Square::isCollidingVerticallyWith(const Square& other) const
{
	return  ((int)this->m_top_left.getY() == (int)other.m_bottom_right.getY() || 
			(int)this->m_top_left.getY() == (int)other.m_top_left.getY()	   ||
			(int)this->m_bottom_right.getY() == (int)other.m_top_left.getY() ||
			(int)this->m_bottom_right.getY() == (int)other.m_bottom_right.getY()) 	&&
			this->isIntersectingWith(other); 
}

bool Square::isCollidingHorizontallyWith(const Diamond& other) const
{
	return ((other.getMinX() >= this->getMinX() && other.getMinX() <= this->getMaxX()) ||
		   (other.getMaxX() <= this->getMaxX() && other.getMaxX() <= this->getMinX())) &&
		   this->isIntersectingWith(other); 
}

bool Square::isCollidingVerticallyWith(const Diamond& other) const
{
	return ((other.getMinY() >= this->getMinY() && other.getMinY() <= this->getMaxY()) ||
		   (other.getMaxY() <= this->getMaxY() && other.getMaxX() <= this->getMinY())) &&
		   this->isIntersectingWith(other); 
}