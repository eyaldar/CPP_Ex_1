#include "ShapesContainer.h"

using namespace std;

ShapesContainer::~ShapesContainer()
{
	destruct();
}

void ShapesContainer::init()
{
	destruct();
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
	for (list<Shape*>::const_iterator it = m_shapes.cbegin(); it != m_shapes.cend(); ++it)
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

Shape* ShapesContainer::collideShapes(Shape* firstShape, Shape* secondShape, bool collideVertically)
{
	Shape* surviver;

	bool isFirstMovingFasterHorizontally = firstShape->compareHorizontalSpeedTo(secondShape) > 0;
	bool isFirstMovingFasterVertically = firstShape->compareVerticalSpeedTo(secondShape) > 0;
	bool isSecondAreaBigger = firstShape->compareAreaTo(secondShape) < 0;

	if(((isFirstMovingFasterHorizontally && collideVertically) ||
		(isFirstMovingFasterVertically && !collideVertically)) && isSecondAreaBigger)
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

Shape* ShapesContainer::findShape(const Point& coordinates, const Shape* except) const
{
	for (list<Shape*>::const_reverse_iterator it = m_shapes.crbegin(); it != m_shapes.crend(); ++it)
	{
		if(*it != except && (*it)->contains(coordinates))
		{
			return *it;
		}
	}

	return NOT_FOUND;
}

int ShapesContainer::getShapesNum() const
{
	return m_shapes.size();
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

	throw "Couldn't find iterator for the given shape !";
}

// File operations

void ShapesContainer::save(ofstream& outFile) const
{
	int size = m_shapes.size();

	// Saves the shapes num
	outFile.write((const char*)&size, sizeof(size));

	// Saves the shapes
	for (list<Shape*>::const_iterator it = m_shapes.begin(); it != m_shapes.end(); ++it)
	{
		(*it)->saveType(outFile);

		(*it)->save(outFile);
	}
}

void ShapesContainer::load(ifstream& inFile)
{
	int size;
	char typeName[TYPELEN+1];

	// Initialize the container
	init();

	// Loads the shapes num
	inFile.read((char*)&size, sizeof(size));

	// Load the shapes
	for (int shapeIndex = 0; shapeIndex < size; shapeIndex++)
	{
		ShapeFactory::getInstance().getTypeFromFile(inFile, typeName);

		Shape* shape = ShapeFactory::getInstance().create(typeName, &inFile);

		addShape(shape);
	}
}