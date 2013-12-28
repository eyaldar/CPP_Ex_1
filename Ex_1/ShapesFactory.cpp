#include "ShapesFactory.h"

using namespace std;

Shape* ShapeFactory::create(const char* typeName, ifstream* inFile) const
{
	// Analyze type
	//if(strncmp(typeName, Square::TYPE_NAME, TYPELEN) == 0)
	if(strncmp(typeName, "Square", TYPELEN) == 0)
	{
		return new Square(inFile);
	}
	//else if(strncmp(typeName, Diamond::TYPE_NAME, TYPELEN) == 0)
	else if(strncmp(typeName,"Diamond", TYPELEN) == 0)
	{
		return new Diamond(inFile);
	}

	throw InvalidTypeNameException(typeName);
}

char* ShapeFactory::getTypeFromFile(std::ifstream& inFile, char* buf) const
{
	//Read type
	inFile.read((char*)buf, TYPELEN);
	buf[TYPELEN] = '\0';
	return buf;
}
