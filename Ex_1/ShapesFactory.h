#ifndef __SHAPES_FACTORY__
#define __SHAPES_FACTORY__

#include <fstream>
#include <string.h>

#include "Shape.h"
#include "Square.h"
#include "Diamond.h"
#include "InvalidTypeNameException.h"

class ShapeFactory{
public:
	static ShapeFactory& getInstance()
	{
		static ShapeFactory instance;
		return instance;
	}

	Shape* create(const char* typeName, std::ifstream* inFile = NULL) const throw(InvalidTypeNameException);

	char* getTypeFromFile(std::ifstream& inFile, char* buf) const;

private:
	ShapeFactory() {}
};

#endif