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
	Point(int x, int y)
	: m_x(x), m_y(y) {}

	void draw(char ch) const;
	void init(int x, int y);

	void setX(int x);
	int getX() const;

	void setY(int y);
	int getY() const;

private:
	int m_x;
	int m_y;
};

#endif