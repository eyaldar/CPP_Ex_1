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