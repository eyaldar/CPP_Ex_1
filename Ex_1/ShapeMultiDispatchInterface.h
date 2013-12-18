#ifndef __SHAPE_MULTI_DISPATCH_INTERFACE__
#define __SHAPE_MULTI_DISPATCH_INTERFACE__

class Shape;
class Square;
class Diamond;

class ShapeMultiDispatchInterface{

public:

	// Shape
	virtual bool isCollidingHorizontallyWith(const Shape&) const = 0; 
	virtual bool isCollidingVerticallyWith(const Shape&) const = 0;

	// Square
	virtual bool isCollidingHorizontallyWith(const Square&) const = 0; 
	virtual bool isCollidingVerticallyWith(const Square&) const = 0;

	// Diamond
	virtual bool isCollidingHorizontallyWith(const Diamond&) const = 0; 
	virtual bool isCollidingVerticallyWith(const Diamond&) const = 0;

};

#endif