#include "ShapesContainer.h"

using namespace std;

ShapesContainer::~ShapesContainer()
{
	destruct();
}

void ShapesContainer::init()
{
	destruct();

	m_shapes.clear();
}

void ShapesContainer::destruct()
{
	for (list<Shape*>::iterator it = m_shapes.begin(); it != m_shapes.end(); ++it)
	{
		delete *it;
	}

	m_shapes.clear();
}

void ShapesContainer::addShape(Shape* newShape)
{
	m_shapes.push_back(newShape);
}

void ShapesContainer::removeShape(Shape* shape)
{
	m_shapes.remove(shape);
	delete shape;
}

void ShapesContainer::drawShapes() const
{
	for (list<Shape*>::const_iterator it = m_shapes.begin(); it != m_shapes.end(); ++it)
	{
		(*it)->draw();
	}
}

void ShapesContainer::promoteShape(Shape* shape)
{
	m_shapes.remove(shape);
	m_shapes.push_back(shape);
}

void ShapesContainer::mergeShapes(Shape* firstShape, Shape* secondShape)
{
	bool areIntersecting = firstShape->isIntersectingWith(secondShape);
	bool isFirstAreaBigger = firstShape->compareAreaTo(secondShape) > 0;

	if(!firstShape->contains(secondShape) &&
	   (secondShape->contains(firstShape) ||
	   (areIntersecting && isFirstAreaBigger)  ||
	   (!areIntersecting && !isFirstAreaBigger)))
	{
		list<Shape*>::const_iterator secondIterator = getShapeIterator(secondShape);
		m_shapes.remove(firstShape);
		m_shapes.insert(secondIterator, firstShape);
	}

	removeShape(secondShape);
}

Shape* ShapesContainer::collideShapes(Shape* firstShape, Shape* secondShape, bool collideHorizontally)
{
	Shape* surviver;

	bool isFirstMovingFasterHorizontally = firstShape->compareHorizontalSpeedTo(secondShape) > 0;
	bool isFirstMovingFasterVertically = firstShape->compareVerticalSpeedTo(secondShape) > 0;
	bool isSecondAreaBigger = firstShape->compareAreaTo(secondShape) < 0;

	if(((isFirstMovingFasterHorizontally && collideHorizontally) ||
		(isFirstMovingFasterVertically && !collideHorizontally)) && isSecondAreaBigger)
	{
		removeShape(firstShape);
		surviver = secondShape;
	}
	else
	{
		removeShape(secondShape);
		surviver = firstShape;
	}
	
	return surviver;
}

void ShapesContainer::getShapesRelations(Shape* firstShape, Shape* secondShape, 
									bool& hasSubsetRelation, bool& hasIntersectionRelation) const
{
		hasIntersectionRelation = firstShape->isIntersectingWith(secondShape);
								
		hasSubsetRelation = (firstShape->contains(secondShape) ||
							 secondShape->contains(firstShape));
}

Shape* ShapesContainer::findShape(const Point& coordinates, const Shape* except) const
{
	for (list<Shape*>::const_iterator it = m_shapes.begin(); it != m_shapes.end(); ++it)
	{
		if(*it != except && (*it)->contains(coordinates))
		{
			return *it;
		}
	}

	return NOT_FOUND;
}

list<Shape*>::const_iterator ShapesContainer::getShapeIterator(const Shape* shape) const
{
	for (list<Shape*>::const_iterator it = m_shapes.begin(); it != m_shapes.end(); ++it)
	{
		if(*it == shape)
		{
			return it;
		}
	}

	throw "Couldn't find shape was not found in the container!";
}

