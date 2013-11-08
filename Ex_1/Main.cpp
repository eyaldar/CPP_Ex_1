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
		sc.init();

		sc.addSquare(1, 2, 30, 'H');
		sc.addSquare(4, 3, 30, 'A');
		sc.addSquare(5, 6, 30, 'M');
		sc.addSquare(7, 7, 30, 'D');	

		sc.removeSquare(1);

		sc.addSquare(3, 6, 10, '%');

		sc.drawSquares();
	}
	catch(const string& error)
	{
		cerr << "Got error: '"<< error << "'";
	}
}