#ifndef __INVALID_TYPE_NAME_EXCEPTION_H__
#define __INVALID_TYPE_NAME_EXCEPTION_H__

#include "Exception.h"

#include <iostream>

class InvalidTypeNameException : public Exception{
public:
	InvalidTypeNameException(const std::string& shapeTypeName)
		: m_type_name(shapeTypeName) {}

	virtual void print() const;

private:
	std::string m_type_name;
};

#endif