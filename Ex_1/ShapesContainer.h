#ifndef __SHAPES_CONTAINER_H__
#define __SHAPES_CONTAINER_H__

#include <list>

#include "Shape.h"
#include "ShapesFactory.h"
#include "InvalidTypeNameException.h"

#define NOT_FOUND NULL

class ShapesContainer {
public:

	ShapesContainer() 
	{
		init();
		m_shapes.resize(10);
	}

	~ShapesContainer();

	void init();
	void addShape(Shape* Shape);

	void removeShape(Shape*);
	void promoteShape(Shape*);
	void mergeShapes(Shape*, Shape*);
	
	void drawShapes() const;
	Shape* findShape(const Point& coordinates, const Shape* except = NULL) const;
	int getShapesNum() const;

	// File operations
	void save(std::ofstream& outFile) const;
	void load(std::ifstream& inFile) throw (InvalidTypeNameException);

private:	

	std::list<Shape*> m_shapes;

	void destruct();
	std::list<Shape*>::const_iterator getShapeIterator(const Shape* shape) const;
};

#endif