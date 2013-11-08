#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "Point.h"

class Square 
{
public:
	Square(Point& point, unsigned int side_length, char ch)
	: m_top_left(point), m_side_length(side_length), m_draw_char(ch) 
	{
		validateChar(ch);
	}

	Square(int x, int y, unsigned int side_length, char ch)
	: m_top_left(x,y), m_side_length(side_length), m_draw_char(ch) 
	{
		validateChar(ch);
	}

	explicit Square(const Square&);

	void draw();
private:
	unsigned int m_side_length;
	Point m_top_left;
	char m_draw_char;

	bool isValidChar(char);
	void validateChar(char);
};

#endif