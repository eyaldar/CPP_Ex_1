#ifndef __Rect_H__
#define __Rect_H__

#include "Point.h"

class Rect 
{
public:
	Rect(Point& point, unsigned int side_length, char ch)
	: m_top_left(point), m_side_length(side_length), m_draw_char(ch) 
	{
		validateChar(ch);
	}

	Rect(int x, int y, unsigned int side_length, char ch)
	: m_top_left(x,y), m_side_length(side_length), m_draw_char(ch) 
	{
		validateChar(ch);
	}


private:
	unsigned int m_side_length;
	Point m_top_left;
	char m_draw_char;

	bool isValidChar(char);
	void validateChar(char);
};

#endif __Rect_H__