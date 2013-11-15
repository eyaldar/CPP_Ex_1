#include "SquaresApp.h"

void SquaresApp::init()
{
	m_squares.init(MAX_AVAILABLE_SQUARES);
	initMainMenu();
}

void SquaresApp::initMainMenu()
{
	m_app_main_menu.init(8);

	m_app_main_menu.set(0, "Add a new square.");
	m_app_main_menu.set(1, "Draw all squares.");
	m_app_main_menu.set(2, "Select square.");
	m_app_main_menu.set(7, "Exit.");
}

void SquaresApp::initSquareMenu()
{
	m_app_square_menu.init(5);

	m_app_square_menu.set(0, "Cancel selection.");
	m_app_square_menu.set(1, "Delete square.");
	m_app_square_menu.set(2, "Show square on top.");
	m_app_square_menu.set(3, "Merge with other square.");
	m_app_square_menu.set(4, "Return.");
}