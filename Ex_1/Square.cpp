#include "Square.h"
#include "Gotoxy.h"

#include <math.h>
#include <string>
using namespace std;

bool Square::isValidChar(char ch)
{
	return ch != '@';
}

void Square::validateChar(char ch)
{
	if(!isValidChar(ch))
	{
		throw string("Invalid char! using '@' is not allowed!");
	}
}

void Square::draw()
{
	int left = m_top_left.getX();
	int top = m_top_left.getY();
	int right = left + m_side_length;
	int bottom = top + m_side_length;
	Point p;

	for (unsigned int lengthIndex = 0; lengthIndex < m_side_length; lengthIndex++)
	{
		p.init(left + lengthIndex, top);
		p.draw(m_draw_char);

		p.init(left, top + lengthIndex);
		p.draw(m_draw_char);

		p.init(left + lengthIndex, bottom);
		p.draw(m_draw_char);

		p.init(right, top + lengthIndex);
		p.draw(m_draw_char);
	}

	p.init(right, bottom);
	p.draw(m_draw_char);
}