#ifndef __SQUARES_APP_H__
#define __SQUARES_APP_H__

#include "Menu.h"
#include "Point.h"
#include "SquaresContainer.h"

class SquaresApp
{
public:
	SquaresApp()
	: m_selected_square_index(-1)
	{
	}

	void init();

private:
	static const int MAX_AVAILABLE_SQUARES = 10;

	Menu m_app_main_menu;
	Menu m_app_square_menu;
	SquaresContainer m_squares;
	int	m_selected_square_index;

	void initMainMenu();
	void initSquareMenu();
};

#endif