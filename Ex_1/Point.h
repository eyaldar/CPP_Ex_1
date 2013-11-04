#ifndef __POINT_H__
#define __POINT_H__

class Point 
{
public:
	Point()
	: m_x(0), m_y(0) {}
	Point(const Point& point)
	: m_x(point.m_x), m_y(point.m_y){}
	Point(int x, int y)
	: m_x(x), m_y(y) {}
private:
	int m_x;
	int m_y;
};

#endif __POINT_H__