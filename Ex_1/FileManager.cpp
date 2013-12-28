#include "FileManager.h"

using namespace std;

string FileManager::getFileNameFromInput(const string& fileExtension) const
{
	string filename;

	cout << "Please enter file name without extension :" << endl;
	cin >> filename;

	while(filename.length() < 1)
	{
		cerr << "Invalid file name!" << endl << endl << endl;

		cout << "Please enter file name without extension :" << endl;
		cin >> filename;
	}

	filename = filename + fileExtension;

	return filename;
}

void FileManager::saveFile(const string& filename, const ShapesContainer& container, bool openBinary) const
{
	ofstream outFile;

	if(openBinary)
	{
		outFile.open(filename, ios_base::trunc | ios_base::out | ios_base::binary);
	}
	else
	{
		outFile.open(filename, ios_base::trunc | ios_base::out);
	}

	if(outFile)
	{
		container.save(outFile);

		outFile.close();
	}
}

void FileManager::loadFile(const string& filename, ShapesContainer& container, bool openBinary) const
{
	ifstream inFile;

	if(openBinary)
	{
		inFile.open(filename, ios_base::in | ios_base::binary);
	}
	else
	{
		inFile.open(filename, ios_base::in);
	}

	if(!inFile)
	{
		throw FileNotFoundException(filename);
	}

	container.load(inFile);

	inFile.close();
}