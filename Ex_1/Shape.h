#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "Point.h"
#include <iostream>

class Square;

class Shape {
public:

	Shape(char drawChar = '@', char selectionChar = '@')
		: m_draw_char(drawChar), m_selection_char(selectionChar) {}

	void setShift(const Point& newShift);
	const Point& getShift() const;
	virtual void setShiftByInput();

	void setSelectionChar(char ch);

	virtual void move() = 0; 

	virtual void input() = 0;

	void draw(bool useMatrix = false) const;
	void drawAsSelected(bool useMatrix = false) const;
	void drawAsFilled(bool useMatrix = false) const;
	void clear(bool useMatrix = false) const;
	void clearAsFilled(bool useMatrix = false) const;
	bool isCollidingWith(const Shape*) const; 

	virtual unsigned int getArea() const = 0;

	virtual bool contains(const Point&) const = 0;
	virtual bool contains(const Shape*) const = 0;
	virtual bool isIntersectingWith(const Shape*) const = 0;

	virtual bool isCollidingHorizontallyWith(const Shape*) const = 0; 
	virtual bool isCollidingVerticallyWith(const Shape*) const = 0;
	virtual bool isWithinScreenBounds() const = 0;

	// Compares to squares by area
	// Returns 0 if the areas are equal, in case this shape is bigger returns positive number
	// otherwise returns negative number.
	int compareAreaTo(const Shape*) const;

	// Compares to squares by horizontal shift
	// Returns 0 if the speeds are equal, in case this shape is faster returns positive number
	// otherwise returns negative number.
	double compareHorizontalSpeedTo(const Shape*) const;

	// Compares to squares by vertical shift
	// Returns 0 if the speeds are equal, in case this shape is faster returns positive number
	// otherwise returns negative number.
	double compareVerticalSpeedTo(const Shape*) const;

	// Multi dispatch methods
	virtual bool contains(const Square*) const = 0;
	virtual bool isIntersectingWith(const Square*) const = 0;
	virtual bool isCollidingHorizontallyWith(const Square*) const = 0; 
	virtual bool isCollidingVerticallyWith(const Square*) const = 0;

protected:
	char m_selection_char;
	char m_draw_char;
	Point m_shift;

	virtual void draw(char ch, bool useMatrix = false) const = 0;
	virtual void drawAsFilled(char ch, bool useMatrix = false) const = 0;
};

#endif