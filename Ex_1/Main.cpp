#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "Menu.h"
#include "SquaresContainer.h"
#include "Gotoxy.h"

using namespace std;

void main()
{
	try
	{
		//system("cls");
		//
		//_flushall();

		//int x=1;
		//int y=1;

		//// esc (Ascii 27) ends the loop
		//while(!_kbhit() || _getch()!=27)
		//{
		//	gotoxy(x,y);
		//	cout << "*" << endl;
		//	Sleep(50);
		//	gotoxy(x,y);
		//	cout << " " << endl;
		//	++x;
		//	if(x>79) {x=1;}
		//	++y;
		//	if(y>20) {y=1;}
		//}

		SquaresContainer sc;
		sc.init(10);

		sc.addSquare(1, 1, 20, 'A');
		sc.addSquare(2, 2, 20, 'B');
		sc.addSquare(3, 3, 20, 'C');
		sc.addSquare(4, 4, 20, 'D');
		sc.addSquare(5, 5, 20, 'E');
		sc.addSquare(6, 6, 20, 'F');
		sc.addSquare(7, 7, 20, 'G');
		sc.addSquare(8, 8, 20, 'H');	
		sc.addSquare(9, 9, 20, 'I');
		sc.addSquare(10, 10, 20, 'J');
		sc.addSquare(11, 11, 20, 'K');	

		sc.removeSquare(1);

		sc.addSquare(2, 2, 10, '%');

		sc.drawSquares();

		clrscr();

		sc.selectSquareByCoordinates(13,14);

		clrscr();

		sc.promoteSquare(6);
		sc.drawSquares();
	}
	catch(const string& error)
	{
		cerr << "Got error: '"<< error << "'";
	}
}