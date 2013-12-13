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

	void copyCurrentState();
	void printDiff();
	void updateScreenMatrix(int x, int y, char ch);
	void clearScreenMatrix();
	bool isWithinScreenBoundaries(int x, int y);

private:
	char prevScreenMatrix[SCREEN_RIGHT_BOUNDARY][SCREEN_BOTTOM_BOUNDARY];
	char currScreenMatrix[SCREEN_RIGHT_BOUNDARY][SCREEN_BOTTOM_BOUNDARY];

	ScreenMatrix()
	{
		init();
	}

	void init();
	void initScreenMatrix(char screenMatrix[SCREEN_RIGHT_BOUNDARY][SCREEN_BOTTOM_BOUNDARY]);
};

#endif