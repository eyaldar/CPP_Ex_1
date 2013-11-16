#include "SquaresApp.h"

using namespace std;

void main()
{
	try
	{
		SquaresApp& app = SquaresApp::getInstance();
		app.run();
	}
	catch(const string& error)
	{
		cerr << "Got error: '"<< error << "'";
	}
}