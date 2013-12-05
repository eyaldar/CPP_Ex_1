#include "SquaresApp.h"
using namespace std;

void SquaresApp::init()
{
	m_selected_square = NULL;

	m_squares.init();
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
				addSquareByInput();
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
	Point& selectionPoint = createPointByInput();
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
				Point& selectionPoint = createPointByInput();
				Square* secondSquare =  m_squares.findSquare(selectionPoint, m_selected_square);

				if(secondSquare != NOT_FOUND)
					m_squares.mergeSquares(*m_selected_square, *secondSquare);

				break;
			}
			case ADD_ANIMATION:
			{
				Point shift = createShiftByInput();
				m_selected_square->setShift(shift);

				drawMove();

				break;
			}
		}
	}
	
	clrscr();
	m_squares.drawSquares();
	waitForEscape();
}

Point SquaresApp::createShiftByInput() const
{
	double x,y;

	cout << "Please enter the required shift in X axis [ Value between -1 and 1 ] :";
	cin >> x;

	while(x > 1 || x < -1)
	{
		cerr << "Given shift in X axis is too big !." << endl << endl << endl;

		cout << "Please enter the required shift in X axis [ Value between -1 and 1 ] :";
		cin >> x;
	}

	cout << "Please enter the required shift in Y axis [ Value between -1 and 1 ] :";
	cin >> y;

	while(y > 1 || y < -1)
	{
		cerr << "Given shift in Y axis is too big !." << endl << endl << endl;

		cout << "Please enter the required shift in Y axis [ Value between -1 and 1 ] :";
		cin >> y;
	}

	return Point(x,y);
}

Point SquaresApp::createPointByInput() const
{
	double x,y;

	cout << "Please enter the X coordinate :";
	cin >> x;
	cout << "Please enter the Y coordinate :";
	cin >> y;

	return Point(x,y);
}

void SquaresApp::addSquareByInput()
{
	double sideLength;
	char ch;
	Point topLeft = createPointByInput();

	cout << "Please enter the side length [At least 1] :";
	cin >> sideLength;

	while(sideLength < 1)
	{
		cerr << "Invalid side length !." << endl << endl << endl;

		cout << "Please enter the side length [At least 1] :";
		cin >> sideLength;
	}

	cout << "Please enter the square character ['@' is not allowed]:";
	cin >> ch;

	while(ch == SELECTION_CHAR)
	{
		cerr << "Invalid character ! Please insert different square character ." << endl << endl << endl;

		cout << "Please enter the square character ['@' is not allowed]:";
		cin >> ch;
	}

	m_squares.addSquare(topLeft, (unsigned int)sideLength, ch);
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

void SquaresApp::drawMove() const
{
	Square oldSquare(*m_selected_square);

	clrscr();
	drawSquaresWithSelection();

	while(!_kbhit() || _getch()!=27)
	{
		if(m_selected_square->move())
		{
			oldSquare.draw(' ');
			m_squares.drawIntersectingWith(oldSquare);
			m_squares.drawIntersectingWith(*m_selected_square);
			m_selected_square->draw(SELECTION_CHAR);

			oldSquare.copyFrom(*m_selected_square);
		}
		Sleep(100);
	}
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
		   lastOption == DOUBLE_ANIMATION || 
		   lastOption == BEGIN_SQUARE_MENU;
}