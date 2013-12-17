#include "Shape.h"

using namespace std;

void Shape::draw(bool useMatrix) const
{
	draw(m_draw_char, useMatrix);
}

void Shape::drawAsSelected(bool useMatrix) const
{
	draw(m_selection_char, useMatrix);
}

void Shape::drawAsFilled(bool useMatrix) const
{
	drawAsFilled(m_draw_char, useMatrix);
}

void Shape::clear(bool useMatrix) const
{
	draw(' ', useMatrix);
}

void Shape::clearAsFilled(bool useMatrix) const
{
	drawAsFilled(' ', useMatrix);
}

double Shape::compareHorizontalSpeedTo(const Shape* other) const
{		
	double thisAbsShift = abs(this->m_shift.getX());
	double otherAbsShift = abs(other->m_shift.getX());

	return thisAbsShift - otherAbsShift;
}

double Shape::compareVerticalSpeedTo(const Shape* other) const
{		
	double thisAbsShift = abs(this->m_shift.getY());
	double otherAbsShift = abs(other->m_shift.getY());

	return thisAbsShift - otherAbsShift;
}

int Shape::compareAreaTo(const Shape* other) const
{		
	int thisArea = this->getArea();
	int otherArea = other->getArea();

	return thisArea - otherArea;
}

const Point& Shape::getShift() const
{
	return m_shift;
}

void Shape::setShift(const Point& point)
{
	m_shift = Point(point);
}

bool Shape::isCollidingWith(const Shape* other) const
{
	return isCollidingHorizontallyWith(other) || isCollidingVerticallyWith(other);
}

void Shape::setShiftByInput()
{
	double x,y;

	cout << "Please enter the required shift in X axis [ Value between -1 and 1 ] :";
	cin >> x;

	while(x > 1 || x < -1)
	{
		cerr << "Given shift in X axis is too big !." << endl << endl << endl;

		cout << "Please enter the required shift in X axis [ Value between -1 and 1 ] :";
		cin >> x;
	}

	cout << "Please enter the required shift in Y axis [ Value between -1 and 1 ] :";
	cin >> y;

	while(y > 1 || y < -1)
	{
		cerr << "Given shift in Y axis is too big !." << endl << endl << endl;

		cout << "Please enter the required shift in Y axis [ Value between -1 and 1 ] :";
		cin >> y;
	}

	setShift(Point(x,y));
}

bool Shape::isWithinScreenBounds() const
{
	return SCREEN_TOP_BOUNDARY <= getMinY() && 
		   getMaxY() <= SCREEN_BOTTOM_BOUNDARY  &&
		   SCREEN_LEFT_BOUNDARY <= getMinX() &&
		   getMaxX() <= SCREEN_RIGHT_BOUNDARY;
}

void Shape::deflectOnBounds()
{
	if(isWithinScreenBounds())
	{
		if(SCREEN_LEFT_BOUNDARY > getMinX() + m_shift.getX() ||
			SCREEN_RIGHT_BOUNDARY <= getMaxX() + m_shift.getX())
		{
			m_shift.setX(m_shift.getX() * -1);
		}

		if(SCREEN_TOP_BOUNDARY > getMinY() + m_shift.getY() ||
		   SCREEN_BOTTOM_BOUNDARY <= getMaxY() + m_shift.getY())
		{
			m_shift.setY(m_shift.getY() * -1);
		}
	}
}

// File operations

void Shape::saveType(ofstream& outFile) const
{
	char type[TYPELEN + 1];

	// in VC++ typeid([instance]).name() == "class [type]"
	// strlen("class ") == 6
	strncpy_s(type, typeid(*this).name() + 6, TYPELEN);

	outFile.write((const char*)type, TYPELEN);
}

void Shape::save(ofstream& outFile) const
{
	// Save Shift
	m_shift.save(outFile);

	// Save Draw Char
	outFile.write(&m_draw_char, sizeof(m_draw_char));

	// Save Selection Char
	outFile.write(&m_selection_char, sizeof(m_selection_char));
}

void Shape::load(ifstream& inFile)
{
	// Load Shift
	m_shift.load(inFile);

	// Load Draw Char
	inFile.read(&m_draw_char, sizeof(m_draw_char));

	// Load Selection Char
	inFile.read(&m_selection_char, sizeof(m_selection_char));
}