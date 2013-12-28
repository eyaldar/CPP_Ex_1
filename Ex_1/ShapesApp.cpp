#include "ShapesApp.h"
using namespace std;

static const string BINARY_FILE_EXTENSION = ".dat";
static const string TEXTUAL_FILE_EXTENSION = ".txt";

void ShapesApp::init()
{
	m_selected_shape = NULL;

	m_shapes.init();
	initMainMenu();
	initShapeMenu();
	initAddShapeMenu();
}

void ShapesApp::initMainMenu()
{
	m_app_main_menu.init(NUM_OF_MAIN_MENU_OPTIONS);

	m_app_main_menu.set(0, "Add a new Shape.");
	m_app_main_menu.set(1, "Draw all Shapes.");
	m_app_main_menu.set(2, "Select Shape.");
	m_app_main_menu.set(3, "Save to textual file.");
	m_app_main_menu.set(4, "Load from textual file.");
	m_app_main_menu.set(5, "Save to binary file.");
	m_app_main_menu.set(6, "Load from binary file.");
	m_app_main_menu.set(EXIT_OPTION, "Exit.");
}

void ShapesApp::initShapeMenu()
{
	m_app_shape_menu.init(NUM_OF_SHAPE_MENU_OPTIONS);

	m_app_shape_menu.set(0, "Cancel selection.");
	m_app_shape_menu.set(1, "Remove Shape.");
	m_app_shape_menu.set(2, "Move to top.");
	m_app_shape_menu.set(3, "Merge with other Shape.");
	m_app_shape_menu.set(4, "Add animation");
	m_app_shape_menu.set(5, "Show doubled animation");
}

void ShapesApp::initAddShapeMenu()
{
	m_add_shape_menu.init(NUM_OF_ADD_SHAPE_MENU_OPTIONS);

	m_add_shape_menu.set(0, "Square");
	m_add_shape_menu.set(1, "Diamond");
}

void ShapesApp::run()
{
	unsigned int l_option = 0;

	while (l_option != EXIT_OPTION)
	{
		l_option = m_app_main_menu.choose();
		switch(l_option)
		{
			case ADD_SHAPE:
				{
					int chosenType = m_add_shape_menu.choose();
					const char* typeName = m_add_shape_menu.get(chosenType);

					try
					{
						Shape* shape = ShapeFactory::getInstance().create(typeName);
						m_shapes.addShape(shape);
					}
					catch(InvalidTypeNameException e)
					{
						printException(e);
					}
				}
				// Allows this case to continue to the next case, as it needs to be printed anyway...
			case DRAW_SHAPES:
				{
					clrscr();
					m_shapes.drawShapes();
					waitForEscape();
					break;
				}
			case SELECT_SHAPE:
				{
					selectShape();

					if(m_selected_shape != NOT_FOUND)
						runShapeMenu();

					break;
				}

			case SAVE_TEXTUAL_FILE:
				{
					string filename = FileManager::getInstance().getFileNameFromInput(TEXTUAL_FILE_EXTENSION);

					FileManager::getInstance().saveFile(filename, m_shapes, false);

					break;
				}
			case LOAD_TEXTUAL_FILE:
				{
					if(assureLoadOverride())
					{
						string filename = FileManager::getInstance().getFileNameFromInput(TEXTUAL_FILE_EXTENSION);

						try
						{
							FileManager::getInstance().loadFile(filename, m_shapes, false);
						}
						catch(Exception& e)
						{
							printException(e);
						}
					}
					break;
				}
			case SAVE_BINARY_FILE:
				{
					string filename = FileManager::getInstance().getFileNameFromInput(BINARY_FILE_EXTENSION);

					FileManager::getInstance().saveFile(filename, m_shapes, true);

					break;
				}
			case LOAD_BINARY_FILE:
				{
					if(assureLoadOverride())
					{
						string filename = FileManager::getInstance().getFileNameFromInput(BINARY_FILE_EXTENSION);

						try
						{
							FileManager::getInstance().loadFile(filename, m_shapes, true);
						}
						catch(Exception& e)
						{
							printException(e);
						}
					}
					break;
				}
			case EXIT_OPTION:
				return;
		}
	}
}

void ShapesApp::selectShape()
{
	Point selectionPoint;
	selectionPoint.input();

	m_selected_shape = m_shapes.findShape(selectionPoint);

	clrscr();

	drawShapesWithSelection();
	drawBlinkingPoint(selectionPoint);
}

void ShapesApp::runShapeMenu()
{
	unsigned int l_option = BEGIN_SHAPE_MENU;

	while (shouldReturnToShapeMenu(l_option))
	{
		l_option = m_app_shape_menu.choose();
		switch(l_option)
		{
			case CANCEL_SELECTION:
			{
				m_selected_shape = NOT_FOUND;
				break;
			}
			case REMOVE_Shape:
			{
				m_shapes.removeShape(m_selected_shape);
				break;
			}
			case MOVE_TOP:
			{
				m_shapes.promoteShape(m_selected_shape);
				break;
			}
			case MERGE_SHAPE:
			{
				Point selectionPoint;
				selectionPoint.input();

				Shape* secondShape =  m_shapes.findShape(selectionPoint, m_selected_shape);

				if(secondShape != NOT_FOUND)
					m_shapes.mergeShapes(m_selected_shape, secondShape);

				break;
			}
			case ADD_ANIMATION:
			{
				m_selected_shape->setShiftByInput();

				playAnimation();

				break;
			}
			case DOUBLE_ANIMATION:
			{
				Point selectionPoint;
				selectionPoint.input();

				Shape* secondShape =  m_shapes.findShape(selectionPoint, m_selected_shape);

				if(secondShape != NOT_FOUND)
				{
					playDoubleAnimation(secondShape);
				}

				break;
			}
		}
	}
	
	clrscr();
	m_shapes.drawShapes();
	waitForEscape();
}

void ShapesApp::waitForEscape() const
{
	while(!_kbhit() || _getch()!=27)
	{
		Sleep(50);
	}
}

void ShapesApp::drawBlinkingPoint(const Point& point) const
{
	while(!_kbhit() || _getch()!=27)
	{
		point.draw(SELECTION_CHAR);
		Sleep(100);
		point.draw(' ');
		Sleep(100);
	}
}

void ShapesApp::playAnimation() const
{
	clrscr();
	ScreenMatrix::getInstance().clearScreenMatrix();

	while(!_kbhit() || _getch()!=27)
	{
		moveInScreen(m_selected_shape);

		Sleep(100);
	}
}

void ShapesApp::playDoubleAnimation(Shape* secondShape)
{
	bool hasCollided = false;
	bool hasCollidedVertically = false;
	ShapesCollisionDetector collisionManager(*m_selected_shape, *secondShape);

	clrscr();
	ScreenMatrix::getInstance().clearScreenMatrix();

	while(!_kbhit() || _getch()!=27)
	{
		// Collided now
		if(collisionManager.hasCollided())
		{
			hasCollidedVertically = m_selected_shape->isCollidingVerticallyWith(*secondShape);

			m_selected_shape = handleCollision(m_selected_shape, secondShape, hasCollidedVertically);
			playAnimation();
			break;
		}

		collisionManager.updateShapesRelations();

		moveInScreen(m_selected_shape);

		hasCollidedVertically = m_selected_shape->isCollidingHorizontallyWith(*secondShape);
		hasCollided = hasCollidedVertically || m_selected_shape->isCollidingVerticallyWith(*secondShape);

		moveInScreen(secondShape);

		collisionManager.updateShapesRelations();

		// Collision occured in between movements
		if(hasCollided && collisionManager.hasCollided())
		{
			m_selected_shape = handleCollision(m_selected_shape, secondShape, hasCollidedVertically);
			playAnimation();

			break;
		}

		Sleep(100);
	}
}

Shape* ShapesApp::handleCollision(Shape* firstShape, Shape* secondShape, bool hasCollidedVertically)
{
	Shape* surviver = NULL;

	ScreenMatrix::getInstance().copyCurrentState();

	firstShape->drawAsFilled(true);
	secondShape->drawAsFilled(true);

	ScreenMatrix::getInstance().printDiff();

	surviver = ShapesCollisionManager::getInstance().getCollisionSurviver(firstShape, secondShape, hasCollidedVertically);

	if(surviver != firstShape)
	{
		m_shapes.removeShape(firstShape);
	}
	else
	{
		m_shapes.removeShape(secondShape);
	}

	return surviver;
}

void ShapesApp::moveInScreen(Shape* Shape) const
{
	ScreenMatrix::getInstance().copyCurrentState();

	Shape->clear(true);

	Shape->move();

	Shape->draw(true);

	ScreenMatrix::getInstance().printDiff();
}

void ShapesApp::drawShapesWithSelection() const
{
	m_shapes.drawShapes();

	if(m_selected_shape != NOT_FOUND)
	{
		m_selected_shape->drawAsSelected();
	}
}

bool ShapesApp::shouldReturnToShapeMenu(int lastOption) const
{
	return lastOption == ADD_ANIMATION || 
		   lastOption == BEGIN_SHAPE_MENU;
}

bool ShapesApp::assureLoadOverride() const
{
	char answer =  YES;

	if(m_shapes.getShapesNum() > 0)
	{
		cout << "Are you sure you want to lose existing data? [Y or N] : " << endl;
		cin >> answer;

		while(answer != YES && answer != NO)
		{
			cerr << "Please click 'Y' for yes and 'N' for no" << endl << endl << endl;

			cout << "Are you sure you want to lose existing data? [Y or N] : ";
			cin >> answer;
		}
	}

	return answer == YES;
}

void ShapesApp::printException(const Exception& e) const
{
	e.print();

	cout << "Press ESC to continue...";
	waitForEscape();
}