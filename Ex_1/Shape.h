#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <iostream>
#include <typeinfo.h>
#include <string.h>
#include <vector>

#include "Point.h"
#include "ShapeMultiDispatchInterface.h"

#define TYPELEN 2 // length of Type string in file

class Shape : public ShapeMultiDispatchInterface {
public:

	Shape(char drawChar = '@', char selectionChar = '@')
		: m_draw_char(drawChar), m_selection_char(selectionChar) {}

	void setShift(const Point& newShift);
	void setShiftByInput();

	const Point& getShift() const;

	void setSelectionChar(char ch);

	virtual void move() = 0; 

	virtual void input() = 0;

	void draw(bool useMatrix = false) const;
	void drawAsSelected(bool useMatrix = false) const;
	void drawAsFilled(bool useMatrix = false) const;
	void clear(bool useMatrix = false) const;
	void clearAsFilled(bool useMatrix = false) const;
	bool isCollidingWith(const Shape&) const; 

	virtual unsigned int getArea() const = 0;

	virtual bool contains(const Point&) const = 0;
	virtual bool contains(const Shape&) const;
	virtual bool isIntersectingWith(const Shape&) const;

	// Compares to squares by area
	// Returns 0 if the areas are equal, in case this shape is bigger returns positive number
	// otherwise returns negative number.
	int compareAreaTo(const Shape&) const;

	// Compares to squares by horizontal shift
	// Returns 0 if the speeds are equal, in case this shape is faster returns positive number
	// otherwise returns negative number.
	double compareHorizontalSpeedTo(const Shape&) const;

	// Compares to squares by vertical shift
	// Returns 0 if the speeds are equal, in case this shape is faster returns positive number
	// otherwise returns negative number.
	double compareVerticalSpeedTo(const Shape&) const;

	const std::vector<const Point*>& getCorners() const;
	virtual double getMinX() const = 0; 
	virtual double getMaxX() const = 0; 
	virtual double getMinY() const = 0; 
	virtual double getMaxY() const = 0; 

	// File operations
	void saveType(std::ofstream& outFile) const;
	virtual void save(std::ofstream& outFile) const;

protected:
	std::vector<const Point*> m_corner_points;
	char m_selection_char;
	char m_draw_char;
	Point m_shift;

	virtual void draw(char ch, bool useMatrix = false) const = 0;
	virtual void drawAsFilled(char ch, bool useMatrix = false) const = 0;

	bool isWithinScreenBounds() const;
	void deflectOnBounds();
	virtual void updateCorners() = 0;
	virtual void initCornersVector() = 0;

	virtual void load(std::ifstream& inFile);

	void copyFrom(const Shape& other);
};

#endif