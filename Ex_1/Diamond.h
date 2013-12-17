#ifndef __DIAMOND_H__
#define __DIAMOND_H__

#include "Point.h"
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
	: m_center(center), m_radius(radius), Shape('@') {}

	Diamond(int x, int y, unsigned int radius)
	: m_center(x, y), m_radius(radius), Shape('@') {}

	Diamond(const Diamond&);

	virtual void move();

	virtual void input();

	virtual unsigned int getArea() const;

	virtual bool contains(const Point& point) const;
	virtual bool contains(const Shape*) const;
	virtual bool isIntersectingWith(const Shape*) const; 
	virtual bool isCollidingHorizontallyWith(const Shape*) const; 
	virtual bool isCollidingVerticallyWith(const Shape*) const;
	
	virtual double getMinX() const; 
	virtual double getMaxX() const; 
	virtual double getMinY() const; 
	virtual double getMaxY() const; 

	// File operations
	virtual void save(std::ofstream& outFile) const;
	virtual void load(std::ifstream& inFile);

	// Multi dispatch methods
	virtual bool contains(const Square* other) const;
	virtual bool isIntersectingWith(const Square*) const;
	virtual bool isCollidingHorizontallyWith(const Square*) const; 
	virtual bool isCollidingVerticallyWith(const Square*) const;

	virtual bool contains(const Diamond*) const;
	virtual bool isIntersectingWith(const Diamond*) const;
	virtual bool isCollidingHorizontallyWith(const Diamond*) const; 
	virtual bool isCollidingVerticallyWith(const Diamond*) const;

protected:

	virtual void draw(char ch, bool useMatrix = false) const;
	virtual void drawAsFilled(char ch, bool useMatrix) const;

private:
	Point m_center;
	unsigned int m_radius;

	void copyFrom(const Diamond&);
};

#endif