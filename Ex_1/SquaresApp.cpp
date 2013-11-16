#include "SquaresApp.h"
using namespace std;

void SquaresApp::init()
{
	m_selected_square_index = -1;

	m_squares.init(MAX_AVAILABLE_SQUARES);
	initMainMenu();
	initSquareMenu();
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
	m_app_square_menu.set(1, "Delete square.");
	m_app_square_menu.set(2, "Show square on top.");
	m_app_square_menu.set(3, "Merge with other square.");
}

void SquaresApp::run()
{
	unsigned int l_option = 0;

	while (l_option != EXIT_OPTION)
	{
		l_option = m_app_main_menu.choose();
		switch(l_option)
		{
			case 0:
				addSquareByInput();
				break;
			case 1:
				clrscr();
				m_squares.drawSquares();
				waitForEscape();
				break;
			case 2:
				selectSquare();

				if(m_selected_square_index != SquaresContainer::NOT_FOUND)
					runSquareMenu();
				break;
			case EXIT_OPTION:
				return;
		}

		updateMainMenuOptions();
	}
}

void SquaresApp::selectSquare()
{
	Point& selectionPoint = createPointByInput();
	m_selected_square_index = m_squares.findSquareByCoordinates(selectionPoint);

	clrscr();

	drawSquaresWithSelection();
	drawBlinkingPoint(selectionPoint);
}

void SquaresApp::runSquareMenu()
{
	unsigned int l_option = 0;

	l_option = m_app_square_menu.choose();
	switch(l_option)
	{
		case 0:
			m_selected_square_index = SquaresContainer::NOT_FOUND;
			break;
		case 1:
			m_squares.removeSquare(m_selected_square_index);
			break;
		case 2:
			m_squares.promoteSquare(m_selected_square_index);
			break;
		case 3:
			Point& selectionPoint = createPointByInput();
			int secondSquareIndex = m_squares.findSquareByCoordinates(selectionPoint);

			if(secondSquareIndex != SquaresContainer::NOT_FOUND)
				m_squares.intersectSquares(m_selected_square_index, secondSquareIndex);

			break;
	}
	
	clrscr();
	m_squares.drawSquares();
	waitForEscape();
}
Point SquaresApp::createPointByInput() const
{
	int x,y;

	cout << "Please enter the X coordinate :";
	cin >> x;
	cout << "Please enter the Y coordinate :";
	cin >> y;

	return Point(x,y);
}

void SquaresApp::addSquareByInput()
{
	int x,y, sideLength;
	char ch;

	cout << "Please enter the X coordinate for the top left point :";
	cin >> x;
	cout << "Please enter the Y coordinate for the top left point :";
	cin >> y;
	cout << "Please eneter the side length [Natural numbers only] :";
	cin >> sideLength;	
	cout << "Please enter the square character:";
	cin >> ch;

	m_squares.addSquare(x, y, sideLength, ch);
}

void SquaresApp::updateMainMenuOptions()
{
	m_app_main_menu.setAvailability(0, !m_squares.isContainerFull());
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
		point.draw(SquaresContainer::SELECTION_CHAR);
		Sleep(100);
		point.draw(' ');
		Sleep(100);
	}
}

void SquaresApp::drawSquaresWithSelection() const
{
	if(m_selected_square_index != SquaresContainer::NOT_FOUND)
	{
		m_squares.drawSquaresWithSelection(m_selected_square_index);
	}
	else
	{
		m_squares.drawSquares();
	}
}