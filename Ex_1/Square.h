#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "Point.h"
#include "Shape.h"
#include "Diamond.h"
#include <math.h>
#include <string>

class Square : public Shape
{
public:
	static const char* TYPE_NAME;

	Square(std::ifstream* inFile = NULL)
	{
		if(inFile == NULL)
			input();
		else
			load(*inFile);
	}

	Square(const Point& point, unsigned int side_length, char ch)
	: m_top_left(point), m_side_length(side_length), Shape(ch) 
	{
		updateCorners();
		initCornersVector();
	}

	Square(int x, int y, unsigned int side_length, char ch)
	: m_top_left(x, y), m_side_length(side_length), Shape(ch) 
	{
		updateCorners();
		initCornersVector();
	}

	Square(const Square&);

	virtual void move();

	virtual void input();

	virtual unsigned int getArea() const;

	virtual bool contains(const Point& point) const;

	virtual bool isCollidingHorizontallyWith(const Shape&) const; 
	virtual bool isCollidingVerticallyWith(const Shape&) const;
	
	virtual double getMinX() const; 
	virtual double getMaxX() const; 
	virtual double getMinY() const; 
	virtual double getMaxY() const; 

	// File operations
	virtual void save(std::ofstream& outFile) const;

	// Multi dispatch methods
	virtual bool isCollidingHorizontallyWith(const Square&) const; 
	virtual bool isCollidingVerticallyWith(const Square&) const;

	virtual bool isCollidingHorizontallyWith(const Diamond&) const; 
	virtual bool isCollidingVerticallyWith(const Diamond&) const;

protected:

	virtual void draw(char ch, bool useMatrix = false) const;
	virtual void drawAsFilled(char ch, bool useMatrix) const;
	virtual void load(std::ifstream& inFile);

	virtual void updateCorners();
	
	virtual void initCornersVector();

private:

	unsigned int m_side_length;
	Point m_top_left;
	Point m_top_right;
	Point m_bottom_left;
	Point m_bottom_right;

	void copyFrom(const Square&);

};

#endif