#include "SquaresApp.h"
using namespace std;

void SquaresApp::init()
{
	m_selected_square = NULL;

	m_squares.init();
	initMainMenu();
	initSquareMenu();

	InputManager::getInstance().setForbiddenChar(SELECTION_CHAR);
}

void SquaresApp::initMainMenu()
{
	m_app_main_menu.init(NUM_OF_MAIN_MENU_OPTIONS);

	m_app_main_menu.set(0, "Add a new square.");
	m_app_main_menu.set(1, "Draw all squares.");
	m_app_main_menu.set(2, "Select square.");
	m_app_main_menu.set(EXIT_OPTION, "Exit.");
}

void SquaresApp::initSquareMenu()
{
	m_app_square_menu.init(NUM_OF_SQUARE_MENU_OPTIONS);

	m_app_square_menu.set(0, "Cancel selection.");
	m_app_square_menu.set(1, "Remove square.");
	m_app_square_menu.set(2, "Move to top.");
	m_app_square_menu.set(3, "Merge with other square.");
	m_app_square_menu.set(4, "Add animation");
	m_app_square_menu.set(5, "Show doubled animation");
}

void SquaresApp::run()
{
	unsigned int l_option = 0;

	while (l_option != EXIT_OPTION)
	{
		l_option = m_app_main_menu.choose();
		switch(l_option)
		{
			case ADD_SQUARE:
				{
					Square square = InputManager::getInstance().createSquareByInput();
					m_squares.addSquare(square);
				}
				// Allows this case to continue to the next case, as it needs to be printed anyway...
			case DRAW_SQUARES:
				clrscr();
				m_squares.drawSquares();
				waitForEscape();
				break;
			case SELECT_SQUARE:
				selectSquare();

				if(m_selected_square != NOT_FOUND)
					runSquareMenu();
				break;
			case EXIT_OPTION:
				return;
		}
	}
}

void SquaresApp::selectSquare()
{
	Point& selectionPoint = InputManager::getInstance().createPointByInput();
	m_selected_square = m_squares.findSquare(selectionPoint);

	clrscr();

	drawSquaresWithSelection();
	drawBlinkingPoint(selectionPoint);
}

void SquaresApp::runSquareMenu()
{
	unsigned int l_option = BEGIN_SQUARE_MENU;

	while (shouldReturnToSquareMenu(l_option))
	{
		l_option = m_app_square_menu.choose();
		switch(l_option)
		{
			case CANCEL_SELECTION:
			{
				m_selected_square = NOT_FOUND;
				break;
			}
			case REMOVE_SQUARE:
			{
				m_squares.removeSquare(*m_selected_square);
				break;
			}
			case MOVE_TOP:
			{
				m_squares.promoteSquare(*m_selected_square);
				break;
			}
			case MERGE_SQUARE:
			{
				Point& selectionPoint = InputManager::getInstance().createPointByInput();
				Square* secondSquare =  m_squares.findSquare(selectionPoint, m_selected_square);

				if(secondSquare != NOT_FOUND)
					m_squares.mergeSquares(*m_selected_square, *secondSquare);

				break;
			}
			case ADD_ANIMATION:
			{
				Point shift = InputManager::getInstance().createShiftByInput();
				m_selected_square->setShift(shift);

				handleAnimation();

				break;
			}
			case DOUBLE_ANIMATION:
			{
				Point& selectionPoint = InputManager::getInstance().createPointByInput();
				Square* secondSquare =  m_squares.findSquare(selectionPoint, m_selected_square);

				if(secondSquare != NOT_FOUND)
					handleDoubleAnimation(*secondSquare);

				break;
			}
		}
	}
	
	clrscr();
	m_squares.drawSquares();
	waitForEscape();
}

void SquaresApp::waitForEscape() const
{
	while(!_kbhit() || _getch()!=27)
	{
		Sleep(50);
	}
}

void SquaresApp::drawBlinkingPoint(const Point& point) const
{
	while(!_kbhit() || _getch()!=27)
	{
		point.draw(SELECTION_CHAR);
		Sleep(100);
		point.draw(' ');
		Sleep(100);
	}
}

void SquaresApp::handleAnimation() const
{
	clrscr();
	ScreenMatrix::getInstance().clearScreenMatrix();

	while(!_kbhit() || _getch()!=27)
	{
		moveInScreen(*m_selected_square);

		Sleep(100);
	}
}

void SquaresApp::handleDoubleAnimation(Square& secondSquare)
{
	bool hasCollisionOccured = false;

	clrscr();
	ScreenMatrix::getInstance().clearScreenMatrix();

	while(!_kbhit() || _getch()!=27)
	{
		moveInScreen(*m_selected_square);

		if(checkCollision(*m_selected_square, secondSquare))
			break;

		moveInScreen(secondSquare);

		if(checkCollision(*m_selected_square, secondSquare))
			break;

		Sleep(100);
	}

	handleAnimation();
}

bool SquaresApp::checkCollision(Square& firstSquare, Square& secondSquare)
{
	if(firstSquare.isCollidingWith(secondSquare))
	{
		m_selected_square = handleCollision(firstSquare, secondSquare);

		return true;
	}

	return false;
}

Square* SquaresApp::handleCollision(Square& firstSquare, Square& secondSquare)
{
	Square* surviver = NULL;

	ScreenMatrix::getInstance().copyCurrentState();

	firstSquare.drawAsFilled();
	secondSquare.drawAsFilled();

	ScreenMatrix::getInstance().printDiff();

	surviver = m_squares.mergeOnCollision(firstSquare, secondSquare);

	waitForEscape();

	return surviver;
}

void SquaresApp::moveInScreen(Square& square) const
{
	ScreenMatrix::getInstance().copyCurrentState();

	square.draw(' ', true);

	square.move();

	square.draw(true);

	ScreenMatrix::getInstance().printDiff();
}

void SquaresApp::drawSquaresWithSelection() const
{
	m_squares.drawSquares();

	if(m_selected_square != NOT_FOUND)
	{
		m_selected_square->draw(SELECTION_CHAR);
	}
}

bool SquaresApp::shouldReturnToSquareMenu(int lastOption) const
{
	return lastOption == ADD_ANIMATION || 
		   lastOption == BEGIN_SQUARE_MENU;
}