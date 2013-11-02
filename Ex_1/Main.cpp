#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "Menu.h"
#include "Gotoxy.h"

using namespace std;

void main()
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
	Menu menu;
	menu.Init(3);
	menu.choose();
}