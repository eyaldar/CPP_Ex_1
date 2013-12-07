#ifndef __SQUARES_APP_H__
#define __SQUARES_APP_H__

#include "Menu.h"
#include "SquaresContainer.h"
#include "InputManager.h"
#include "Gotoxy.h"
#include <conio.h>

class SquaresApp
{
public:
	
	static SquaresApp& getInstance()
	{
		static SquaresApp instance;
		return instance;
	}

	void init();
	void run();

private:
	static const char SELECTION_CHAR = '@';
	static const int NUM_OF_MAIN_MENU_OPTIONS = 8;
	static const int NUM_OF_SQUARE_MENU_OPTIONS = 8;
	static const int BEGIN_SQUARE_MENU = -1;

	static const int ADD_SQUARE = 0;
	static const int DRAW_SQUARES = 1;
	static const int SELECT_SQUARE = 2;

	static const int CANCEL_SELECTION = 0;
	static const int REMOVE_SQUARE = 1;
	static const int MOVE_TOP = 2;
	static const int MERGE_SQUARE = 3;
	static const int ADD_ANIMATION = 4;
	static const int DOUBLE_ANIMATION = 5;
	static const int EXIT_OPTION = 7;

	Menu m_app_main_menu;
	Menu m_app_square_menu;
	SquaresContainer m_squares;
	Square*	m_selected_square;

	SquaresApp()
	: m_selected_square(NOT_FOUND)
	{
		init();
	}

	void initMainMenu();
	void initSquareMenu();

	void selectSquare();
	void runSquareMenu();
	Square* handleCollision(Square& oldSquare, Square& newSquare);
	void handleDoubleAnimation(Square& secondSquare);

	void waitForEscape() const;
	void drawSquaresWithSelection() const;
	void drawBlinkingPoint(const Point&) const;
	void drawAnimation(Square&, Square&) const;
	bool drawSquareMovement(Square&) const;
	void handleAnimation() const;
	bool shouldReturnToSquareMenu(int lastOption) const;
	void redrawSquareWithSorroundings(const Square& oldSquare, const Square& newSquare) const;
};

#endif