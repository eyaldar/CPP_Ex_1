#ifndef __SHAPES_COLLISION_MANAGER_H__
#define __SHAPES_COLLISION_MANAGER_H__

#include <typeinfo>
#include <string>

#include "Shape.h"
#include "Square.h"
#include "Diamond.h"

class ShapesCollisionManager
{
public:
	static ShapesCollisionManager& getInstance()
	{
		static ShapesCollisionManager instance;
		return instance;
	}

	Shape* getCollisionSurviver(Shape*, Shape*, bool collideVertically);

private:
	ShapesCollisionManager() {}

	Shape* getCollisionSurviver(Diamond*, Diamond*, bool collideVertically);
	Shape* getCollisionSurviver(Square*, Diamond*, bool collideVertically);
	Shape* getCollisionSurviver(Square*, Square*, bool collideVertically);
};

#endif