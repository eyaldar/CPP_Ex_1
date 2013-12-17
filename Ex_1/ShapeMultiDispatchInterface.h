#ifndef __SHAPE_MULTI_DISPATCH_INTERFACE__
#define __SHAPE_MULTI_DISPATCH_INTERFACE__

class Square;
class Diamond;

class ShapeMultiDispatchInterface{

public:

	// Square
	virtual bool contains(const Square*) const = 0;
	virtual bool isIntersectingWith(const Square*) const = 0;
	virtual bool isCollidingHorizontallyWith(const Square*) const = 0; 
	virtual bool isCollidingVerticallyWith(const Square*) const = 0;

	// Diamond
	virtual bool contains(const Diamond*) const = 0;
	virtual bool isIntersectingWith(const Diamond*) const = 0;
	virtual bool isCollidingHorizontallyWith(const Diamond*) const = 0; 
	virtual bool isCollidingVerticallyWith(const Diamond*) const = 0;

};

#endif