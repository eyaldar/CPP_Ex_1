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
	this->m_draw_char = other.m_draw_char;
	this->m_radius = other.m_radius;
	this->m_center = Point(other.m_center);
}

double Diamond::getMinX() const
{
	return m_center.getX() - m_radius;
}

double Diamond::getMaxX() const
{
	return m_center.getX() + m_radius;
}

double Diamond::getMinY() const
{
	return m_center.getY() - m_radius;
}

double Diamond::getMaxY() const
{
	return m_center.getY() + m_radius;
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
}

bool Diamond::contains(const Point& point) const
{
	return true;
}

bool Diamond::contains(const Shape*) const
{
	return contains(this);
}

bool Diamond::isIntersectingWith(const Shape*) const
{
	return isIntersectingWith(this);
}

bool Diamond::isCollidingHorizontallyWith(const Shape*) const
{
	return isCollidingHorizontallyWith(this);
}

bool Diamond::isCollidingVerticallyWith(const Shape*) const
{
	return isCollidingVerticallyWith(this);
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
}

// Multi dispatch methods
bool Diamond::contains(const Square*) const
{
	return true;
}

bool Diamond::isIntersectingWith(const Square*) const
{
	return true;
}

bool Diamond::isCollidingHorizontallyWith(const Square*) const
{
	return true;
}

bool Diamond::isCollidingVerticallyWith(const Square*) const
{
	return true;
}

bool Diamond::contains(const Diamond* other) const
{
	return this->contains(Point(other->getMaxX(), other->getMaxY())) &&
		   this->contains(Point(other->getMinX(), other->getMinY()));
}

bool Diamond::isIntersectingWith(const Diamond* other) const
{
	return false;
}

bool Diamond::isCollidingHorizontallyWith(const Diamond* other) const
{
	return false;
}

bool Diamond::isCollidingVerticallyWith(const Diamond* other) const
{
	return false;
}