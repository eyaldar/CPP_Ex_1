#include "Rect.h"

#include <string>
using namespace std;

bool Rect::isValidChar(char ch)
{
	return ch != '@';
}

void Rect::validateChar(char ch)
{
	if(!isValidChar(ch))
	{
		throw string("Invalid char! using '@' is not allowed!");
	}
}