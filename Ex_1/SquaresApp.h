#ifndef __SQUARES_APP_H__
#define __SQUARES_APP_H__

#include "Menu.h"
#include "SquaresContainer.h"
#include "Gotoxy.h"
#include <conio.h>

class SquaresApp
{
public:
	SquaresApp()
	: m_selected_square_index(SquaresContainer::NOT_FOUND)
	{
		init();
	}

	void init();
	void run();

private:
	static const char SELECTION_CHAR = '@';
	static const int MAX_AVAILABLE_SQUARES = 10;
	static const int NUM_OF_MAIN_MENU_OPTIONS = 8;
	static const int NUM_OF_SQUARE_MENU_OPTIONS = 8;
	static const int EXIT_OPTION = 7;

	Menu m_app_main_menu;
	Menu m_app_square_menu;
	SquaresContainer m_squares;
	int	m_selected_square_index;

	void initMainMenu();
	void initSquareMenu();

	void selectSquare();
	void updateMainMenuOptions();
	void runSquareMenu();
	void addSquareByInput();

	void waitForEscape() const;
	void drawSquaresWithSelection() const;
	void drawBlinkingPoint(const Point&) const;
	Point createPointByInput() const;
};

#endif