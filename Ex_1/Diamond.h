#ifndef __DIAMOND_H__
#define __DIAMOND_H__

#include "Point.h"
#include "Square.h"
#include "Shape.h"

class Diamond : public Shape{
public:
	static const char* TYPE_NAME;

	Diamond(std::ifstream* inFile = NULL)
	{
		if(inFile == NULL)
			input();
		else
			load(*inFile);
	}

	Diamond(const Point& center, unsigned int radius)
	: m_center(center), m_radius(radius), Shape('@') 
	{
		updateCorners();
		initCornersVector();
	}

	Diamond(int x, int y, unsigned int radius)
	: m_center(x, y), m_radius(radius), Shape('@') 
	{
		updateCorners();
		initCornersVector();
	}

	Diamond(const Diamond&);

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

	const Point getDistanceFromCenter(const Point&) const;

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
	Point m_center;
	unsigned int m_radius;

	Point m_top;
	Point m_bottom;
	Point m_left;
	Point m_right;

	void copyFrom(const Diamond&);
};

#endif