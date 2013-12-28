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
	// in case the area is bigger we know the radius is bound to be bigger.
	bool isFirstAreaBigger = firstDiamond->compareAreaTo(*secondDiamond) > 0;

	if(isFirstShapeMovingFaster(firstDiamond, secondDiamond, collideVertically) && isFirstAreaBigger)
	{
		return firstDiamond;
	}
	else
	{
		return secondDiamond;
	}
}

Shape* ShapesCollisionManager::getCollisionSurviver(Square* square, Diamond* diamond, bool collideVertically)
{
	if(isFirstShapeMovingFaster(square, diamond, collideVertically))
	{
		return square;
	}
	else
	{
		return diamond;
	}
}

Shape* ShapesCollisionManager::getCollisionSurviver(Square* firstSquare, Square* secondSquare, bool collideVertically)
{
	bool isSecondAreaBigger = firstSquare->compareAreaTo(*secondSquare) < 0;

	if(isFirstShapeMovingFaster(firstSquare, secondSquare, collideVertically)  && isSecondAreaBigger)
	{
		return secondSquare;
	}
	else
	{
		return firstSquare;
	}
}

bool isFirstShapeMovingFaster(const Shape* firstShape, const Shape* secondShape, bool collideVertically)
{
	bool isFirstMovingFasterHorizontally = firstShape->compareHorizontalSpeedTo(*secondShape) > 0;
	bool isFirstMovingFasterVertically = firstShape->compareVerticalSpeedTo(*secondShape) > 0;

	return (isFirstMovingFasterHorizontally && !collideVertically) ||
		   (isFirstMovingFasterVertically && collideVertically);
}