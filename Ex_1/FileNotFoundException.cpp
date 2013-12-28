#include "FileNotFoundException.h"

using namespace std;

void FileNotFoundException::print() const
{
	cerr << "File: '" << m_filename.c_str() << "' was not found!" << endl << endl << endl;
}