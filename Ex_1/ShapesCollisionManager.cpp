#include "ShapesCollisionManager.h"

using namespace std;

Shape* ShapesCollisionManager::getCollisionSurviver(Shape* firstShape, Shape* secondShape, bool collideVertically)
{
	Shape* surviver = NULL;

	if(typeid(*firstShape) == typeid(Square) && typeid(*secondShape) == typeid(Square))
	{
		surviver = getCollisionSurviver((Square*)firstShape,  (Square*)secondShape, collideVertically);
	}
	else if(typeid(*firstShape) == typeid(Square) && typeid(*secondShape) == typeid(Diamond))
	{
		surviver = getCollisionSurviver((Square*)secondShape,  (Diamond*)firstShape, collideVertically);
	}
	else if(typeid(*firstShape) == typeid(Diamond) && typeid(*secondShape) == typeid(Square))
	{
		surviver = getCollisionSurviver((Square*)firstShape,  (Diamond*)secondShape, collideVertically);
	}
	else if(typeid(*firstShape) == typeid(Diamond) && typeid(*secondShape) == typeid(Diamond))
	{
		surviver = getCollisionSurviver((Diamond*)firstShape,  (Diamond*)secondShape, collideVertically);
	}

	return surviver;
}

Shape* ShapesCollisionManager::getCollisionSurviver(Diamond* firstDiamond, Diamond* secondDiamond, bool collideVertically)
{
	Shape* surviver;

	bool isFirstMovingFasterHorizontally = firstDiamond->compareHorizontalSpeedTo(*secondDiamond) > 0;
	bool isFirstMovingFasterVertically = firstDiamond->compareVerticalSpeedTo(*secondDiamond) > 0;
	bool isFirstAreaBigger = firstDiamond->compareAreaTo(*secondDiamond) > 0;

	if(((isFirstMovingFasterHorizontally && !collideVertically) ||
		(isFirstMovingFasterVertically && collideVertically)) && isFirstAreaBigger)
	{
		surviver = firstDiamond;
	}
	else
	{
		surviver = secondDiamond;
	}
	
	return surviver;

}

Shape* ShapesCollisionManager::getCollisionSurviver(Square* square, Diamond* diamond, bool collideVertically)
{
	Shape* surviver;

	bool isSquareMovingFasterHorizontally = square->compareHorizontalSpeedTo(*diamond) > 0;
	bool isSquareMovingFasterVertically = square->compareVerticalSpeedTo(*diamond) > 0;

	if(((isSquareMovingFasterHorizontally && !collideVertically) ||
		(isSquareMovingFasterVertically && collideVertically)))
	{
		surviver = square;
	}
	else
	{
		surviver = diamond;
	}
	
	return surviver;

}

Shape* ShapesCollisionManager::getCollisionSurviver(Square* firstSquare, Square* secondSquare, bool collideVertically)
{
	Shape* surviver;

	bool isFirstMovingFasterHorizontally = firstSquare->compareHorizontalSpeedTo(*secondSquare) > 0;
	bool isFirstMovingFasterVertically = firstSquare->compareVerticalSpeedTo(*secondSquare) > 0;
	bool isSecondAreaBigger = firstSquare->compareAreaTo(*secondSquare) < 0;

	if(((isFirstMovingFasterHorizontally && !collideVertically) ||
		(isFirstMovingFasterVertically && collideVertically)) && isSecondAreaBigger)
	{
		surviver = secondSquare;
	}
	else
	{
		surviver = firstSquare;
	}
	
	return surviver;
}