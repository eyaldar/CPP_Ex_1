#include "InputManager.h"

using namespace std;

void InputManager::setForbiddenChar(char ch)
{
	m_forbidden_char = ch;
}

Square InputManager::createSquareByInput() const
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

	while(ch == m_forbidden_char)
	{
		cerr << "Invalid character ! Please insert different square character ." << endl << endl << endl;

		cout << "Please enter the square character ['@' is not allowed]:";
		cin >> ch;
	}

	return Square(topLeft, (unsigned int)sideLength, ch);
}

Point InputManager::createShiftByInput() const
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

Point InputManager::createPointByInput() const
{
	double x,y;

	cout << "Please enter the X coordinate :";
	cin >> x;
	cout << "Please enter the Y coordinate :";
	cin >> y;

	return Point(x,y);
}