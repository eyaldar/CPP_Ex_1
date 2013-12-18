#include "Diamond.h"

using namespace std;

static const char* TYPE_NAME = "Diamond";

Diamond::Diamond(const Diamond& other)
	: Shape(other.m_draw_char)
{
	copyFrom(other);
}

void Diamond::copyFrom(const Diamond& other)
{
	Shape::copyFrom(other);
	this->m_radius = other.m_radius;
	this->m_center = Point(other.m_center);
	
	updateCorners();
	initCornersVector();
}

void Diamond::updateCorners()
{
	double xCenter = m_center.getX();
	double yCenter = m_center.getY();

	m_left.init(xCenter - m_radius, yCenter);
	m_top.init(xCenter, yCenter - m_radius);
	m_right.init(xCenter + m_radius, yCenter);
	m_bottom.init(xCenter, yCenter + m_radius);
}

void Diamond::initCornersVector()
{
	m_corner_points.clear();

	m_corner_points.push_back(&m_left);
	m_corner_points.push_back(&m_top);
	m_corner_points.push_back(&m_right);
	m_corner_points.push_back(&m_bottom);
}

double Diamond::getMinX() const
{
	return m_left.getX();
}

double Diamond::getMaxX() const
{
	return m_right.getX();
}

double Diamond::getMinY() const
{
	return m_top.getY();
}

double Diamond::getMaxY() const
{
	return m_bottom.getY();
}

unsigned int Diamond::getArea() const
{
	// 4*(m_radius^2/2) = 2 * m_radius^2 -- calculating the area of 4 right triangles with two side length of [m_radius]
	return 2 * m_radius * m_radius;
}

void Diamond::input()
{
	double radius;

	cout << "Please enter values for the center point :" << endl;
	m_center.input();

	cout << "Please enter the radius length [At least 1] :";
	cin >> radius;

	while(radius < 1)
	{
		cerr << "Invalid radius length !" << endl << endl << endl;

		cout << "Please enter the radius length [At least 1] :";
		cin >> radius;
	}

	m_radius = (int)radius;

	updateCorners();
	initCornersVector();
}

void Diamond::draw(char ch, bool useMatrix) const
{
	drawAsFilled(ch, useMatrix);
}

void Diamond::drawAsFilled(char ch, bool useMatrix) const
{
	Point p;
	int centerX = (int)m_center.getX();
	int centerY = (int)m_center.getY();

	for (unsigned int rowIndex = 0; rowIndex <= m_radius; rowIndex++)
	{
		for (unsigned int columnIndex = 0; columnIndex <= m_radius - rowIndex; columnIndex++)
		{
		// The four statements wil draw quarter of the diamond each

			// Upper right from center
			p.init(centerX + columnIndex, centerY + rowIndex);
			p.draw(ch, useMatrix);

			// Upper left from center
			p.init(centerX - columnIndex, centerY + rowIndex);
			p.draw(ch, useMatrix);

			// Lower right from center
			p.init(centerX + columnIndex, centerY - rowIndex);
			p.draw(ch, useMatrix);

			// Lower left from center
			p.init(centerX - columnIndex, centerY - rowIndex);
			p.draw(ch, useMatrix);
		}
	}
}

void Diamond::move()
{
	deflectOnBounds();

	m_center += m_shift;
	updateCorners();
}

bool Diamond::contains(const Point& point) const
{
	int xDistance = (int)abs(point.getX() - m_center.getX());
	int yDistance = (int)abs(point.getY() - m_center.getY());

	return (xDistance + yDistance) <= (int)m_radius; 
}

bool Diamond::isCollidingHorizontallyWith(const Shape& shape) const
{
	return shape.isCollidingHorizontallyWith(*this);
}

bool Diamond::isCollidingVerticallyWith(const Shape& shape) const
{
	return shape.isCollidingVerticallyWith(*this);
}

// File operations

void Diamond::save(ofstream& outFile) const
{
	Shape::save(outFile);

	// Save center
	m_center.save(outFile);

	// Save radius
	outFile.write((const char*)&m_radius, sizeof(m_radius));
}

void Diamond::load(ifstream& inFile)
{
	Shape::load(inFile);

	// Load center
	m_center.load(inFile);

	// Save radius
	inFile.read((char*)&m_radius, sizeof(m_radius));

	// Initialize corners
	updateCorners();
	initCornersVector();
}

// Multi dispatch methods

bool Diamond::isCollidingHorizontallyWith(const Square& square) const
{
	return ((square.getMinX() >= this->getMinX() && square.getMinX() <= this->getMaxX()) ||
		   (square.getMaxX() <= this->getMaxX() && square.getMaxX() <= this->getMinX())) &&
		  this->isIntersectingWith(square); 
}

bool Diamond::isCollidingVerticallyWith(const Square& square) const
{
	return ((square.getMinY() >= this->getMinY() && square.getMinY() <= this->getMaxY()) ||
		   (square.getMaxY() <= this->getMaxY() && square.getMaxX() <= this->getMinY())) &&
		   this->isIntersectingWith(square); 
}

bool Diamond::isCollidingHorizontallyWith(const Diamond& other) const
{
	return ((other.getMinX() >= this->getMinX() && other.getMinX() <= this->getMaxX()) ||
		   (other.getMaxX() <= this->getMaxX() && other.getMaxX() <= this->getMinX())) &&
		  this->isIntersectingWith(other); 
}

bool Diamond::isCollidingVerticallyWith(const Diamond& other) const
{
	return ((other.getMinY() >= this->getMinY() && other.getMinY() <= this->getMaxY()) ||
		   (other.getMaxY() <= this->getMaxY() && other.getMaxX() <= this->getMinY())) &&
		   this->isIntersectingWith(other); 
}