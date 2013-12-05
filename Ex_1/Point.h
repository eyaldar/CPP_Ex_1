#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>

class Point 
{
public:
	Point()
	: m_x(0), m_y(0) {}
	Point(const Point& point)
	: m_x(point.m_x), m_y(point.m_y){}
	Point(double x, double y)
	: m_x(x), m_y(y) {}

	void draw(char ch) const;
	void init(double x, double y);

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