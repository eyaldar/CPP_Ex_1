#ifndef __SCREEN_MATRIX_H__
#define __SCREEN_MATRIX_H__

#define SCREEN_LEFT_BOUNDARY 0
#define SCREEN_TOP_BOUNDARY 0
#define SCREEN_RIGHT_BOUNDARY 80
#define SCREEN_BOTTOM_BOUNDARY 25

#include "Gotoxy.h"
#include <iostream>

class ScreenMatrix 
{
public:
	
	static ScreenMatrix& getInstance()
	{
		static ScreenMatrix instance;
		return instance;
	}

	void printDiff();
	void updateScreenMatrix(int x, int y, char ch);
	void clearScreenMatrix();

private:
	char currScreenMatrix[SCREEN_RIGHT_BOUNDARY][SCREEN_BOTTOM_BOUNDARY];
	char prevScreenMatrix[SCREEN_RIGHT_BOUNDARY][SCREEN_BOTTOM_BOUNDARY];

	ScreenMatrix()
	{
		init();
	}

	void init();
	void initScreenMatrix(char screenMatrix[SCREEN_RIGHT_BOUNDARY][SCREEN_BOTTOM_BOUNDARY]);
	void copyCurrentState();

	void checkIsInsideBoundaries(int x, int y);
};

#endif