#include "ShapesApp.h"
#include "Diamond.h"
using namespace std;

void main()
{
	try
	{
		ShapesApp& app = ShapesApp::getInstance();
		app.run();
	}
	catch(const string& error)
	{
		cerr << "Got error: '"<< error << "'";
	}
}