#ifndef __FILE_NOT_FOUND_EXCEPTION_H__
#define __FILE_NOT_FOUND_EXCEPTION_H__

#include "Exception.h"

#include <iostream>

class FileNotFoundException : public Exception{
public:
	FileNotFoundException(const std::string& filename)
		: m_filename(filename) {}

	virtual void print() const;

private:
	std::string m_filename;
};

#endif