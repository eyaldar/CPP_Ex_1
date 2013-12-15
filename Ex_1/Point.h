#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>
#include "ScreenMatrix.h"
#include "Gotoxy.h"

class Point 
{
public:
	Point()
	: m_x(0), m_y(0) {}
	Point(double x, double y)
	: m_x(x), m_y(y) {}

	void input();
	void init(double x, double y);

	void draw(char ch, bool useMatrix = false) const;

	void setX(double x);
	double getX() const;

	void setY(double y);
	double getY() const;

	Point& operator+=(const Point& shift);
	bool operator==(const Point& other);
	bool operator!=(const Point& other);
private:
	double m_x;
	double m_y;
};

#endif