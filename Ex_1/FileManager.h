#ifndef __FILE_MANAGER_H__
#define __FILE_MANAGER_H__

#include <iostream>
#include <fstream>

#include "FileNotFoundException.h"
#include "ShapesContainer.h"

class FileManager {
public:
	static FileManager& getInstance()
	{
		static FileManager instance;
		return instance;
	}

	std::string getFileNameFromInput(const std::string& fileExtension) const;

	void saveFile(const std::string& filename, const ShapesContainer& container, bool openBinary) const;
	void loadFile(const std::string& filename, ShapesContainer& container, bool openBinary) const 
		throw (FileNotFoundException, InvalidTypeNameException);

private:
	FileManager() {}
};

#endif