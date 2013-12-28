#include "InvalidTypeNameException.h"

using namespace std;

void InvalidTypeNameException::print() const
{
	cerr << "Invalid type name - Type name: '" << m_type_name.c_str() << "' doesn't exist!" << endl << endl << endl;
}