#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include "Point.h"
#include "Square.h"

class InputManager
{
public:
	
	static InputManager& getInstance()
	{
		static InputManager instance;
		return instance;
	}


	void setForbiddenChar(char ch);

	Point createShiftByInput() const;
	Point createPointByInput() const;
	Square createSquareByInput() const;

private:
	char m_forbidden_char;

	InputManager()
		: m_forbidden_char('@')
	{
	}
};

#endif