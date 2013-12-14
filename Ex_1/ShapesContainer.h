#ifndef __SHAPES_CONTAINER_H__
#define __SHAPES_CONTAINER_H__

#include <list>
#include "Square.h"

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
	Shape* collideShapes(Shape*, Shape*, bool collideHorizontally);
	
	void drawShapes() const;
	Shape* findShape(const Point& coordinates, const Shape* except = NULL) const;

	void getShapesRelations(Shape* firstShape, Shape* secondShape, 
						    bool& hasSubsetRelation, bool& hasIntersectionRelation) const;

private:	

	std::list<Shape*> m_shapes;

	void destruct();
	std::list<Shape*>::const_iterator getShapeIterator(const Shape* shape) const;
};

#endif