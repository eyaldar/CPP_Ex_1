#include "ScreenMatrix.h"

using namespace std;

void ScreenMatrix::init()
{
	initScreenMatrix(prevScreenMatrix);
	initScreenMatrix(currScreenMatrix);
}

void ScreenMatrix::initScreenMatrix(char screenMatrix[SCREEN_RIGHT_BOUNDARY][SCREEN_BOTTOM_BOUNDARY])
{
	for (int rowIndex = SCREEN_TOP_BOUNDARY; rowIndex < SCREEN_BOTTOM_BOUNDARY; rowIndex++)
	{
		for (int columnIndex = SCREEN_LEFT_BOUNDARY; columnIndex < SCREEN_RIGHT_BOUNDARY; columnIndex++)
		{
			screenMatrix[columnIndex][rowIndex] = ' ';
		}
	}
}

void ScreenMatrix::printDiff()
{
	for (int rowIndex = SCREEN_TOP_BOUNDARY; rowIndex < SCREEN_BOTTOM_BOUNDARY; rowIndex++)
	{
		for (int columnIndex = SCREEN_LEFT_BOUNDARY; columnIndex < SCREEN_RIGHT_BOUNDARY; columnIndex++)
		{
			if(currScreenMatrix[columnIndex][rowIndex] != prevScreenMatrix[columnIndex][rowIndex])
			{
				gotoxy(columnIndex, rowIndex);
				cout << currScreenMatrix[columnIndex][rowIndex];
			}
		}
	}
}

void ScreenMatrix::copyCurrentState()
{
	for (int rowIndex = SCREEN_TOP_BOUNDARY; rowIndex < SCREEN_BOTTOM_BOUNDARY; rowIndex++)
	{
		for (int columnIndex = SCREEN_LEFT_BOUNDARY; columnIndex < SCREEN_RIGHT_BOUNDARY; columnIndex++)
		{
			prevScreenMatrix[columnIndex][rowIndex] = currScreenMatrix[columnIndex][rowIndex]; 
		}
	}
}

void ScreenMatrix::clearScreenMatrix()
{
	copyCurrentState();
	initScreenMatrix(currScreenMatrix);
}

void ScreenMatrix::updateScreenMatrix(int x, int y, char ch)
{
	checkIsInsideBoundaries(x, y);

	prevScreenMatrix[x][y] = currScreenMatrix[x][y]; 
	currScreenMatrix[x][y] = ch;
}

void ScreenMatrix::checkIsInsideBoundaries(int x, int y)
{
	if(x < SCREEN_LEFT_BOUNDARY  || 
	   x > SCREEN_RIGHT_BOUNDARY ||
	   y < SCREEN_TOP_BOUNDARY   ||
	   y > SCREEN_BOTTOM_BOUNDARY)
	{
		throw "Given coordinates is out of ScreenMatrix's boundaries!";
	}

}