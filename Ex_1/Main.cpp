#include "SquaresApp.h"
#define DEBUG
using namespace std;

void main()
{
	try
	{
#ifndef DEBUG

		SquaresApp app;
		app.run();
#else
		SquaresContainer sc;
		sc.init(10);

		sc.addSquare(0, 0, 20, 'F');
				
		sc.drawSquares();
		Sleep(500);

		sc.addSquare(1, 1, 7, 'A');
				
		sc.drawSquares();
		Sleep(500);

		sc.addSquare(11, 1, 7, 'B');
				
		sc.drawSquares();
		Sleep(500);

		sc.addSquare(3, 4, 11, '$');
				
		sc.drawSquares();
		Sleep(500);

		sc.addSquare(1, 11, 7, 'D');
				
		sc.drawSquares();
		Sleep(500);

		sc.addSquare(12, 11, 7, 'E');
		Sleep(500);
		
		sc.drawSquares();
		Sleep(500);

		sc.addSquare(50, 10, 21, 'G');
		
		sc.drawSquares();
		Sleep(500);

		sc.addSquare(74, -8, 20, 'H');

		sc.drawSquares();
		Sleep(500);

		sc.addSquare(0, 0, 50, 'I');

		sc.drawSquares();
		Sleep(500);

		sc.addSquare(40, -10, 20, 'J');
		
		sc.drawSquares();
		Sleep(500);	

		clrscr();

		sc.removeSquare(1);

		sc.drawSquares();
		Sleep(500);

		clrscr();

		sc.addSquare(2, 2, 10, '%');

		sc.drawSquares();
		Sleep(2000);

		clrscr();

		Point p(10,12);
		int squareIndex = sc.findSquare(p);
		sc.drawSquares();
		sc.drawSquare(squareIndex, '@');
		p.draw('X');

		Sleep(2000);

		clrscr();

		sc.promoteSquare(2);

		sc.drawSquares();
		Sleep(2000);

		clrscr();

		Point p2(41,13);
		int squareIndex2 = sc.findSquare(p2);

		sc.intersectSquares(squareIndex, squareIndex2);
		sc.drawSquares();

		Sleep(5000);

		clrscr();

		p.init(0, 0);
		squareIndex = sc.findSquare(p);

		p2.init(3, 4);
		squareIndex2 = sc.findSquare(p2);

		sc.intersectSquares(squareIndex, squareIndex2);
		sc.drawSquares();

		Sleep(5000);

		clrscr();

		p.init(50, 10);
		squareIndex = sc.findSquare(p);

		p2.init(40, -10);
		squareIndex2 = sc.findSquare(p2);

		sc.intersectSquares(squareIndex, squareIndex2);
		sc.drawSquares();

		Sleep(5000);
#endif
	}
	catch(const string& error)
	{
		cerr << "Got error: '"<< error << "'";
	}
}