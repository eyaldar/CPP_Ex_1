#ifndef __ShapeS_APP_H__
#define __ShapeS_APP_H__

#include "Menu.h"
#include "ShapesContainer.h"
#include "Gotoxy.h"
#include <conio.h>

class ShapesApp
{
public:
	
	static ShapesApp& getInstance()
	{
		static ShapesApp instance;
		return instance;
	}

	void init();
	void run();

private:
	static const char SELECTION_CHAR = '@';
	static const int NUM_OF_MAIN_MENU_OPTIONS = 8;
	static const int NUM_OF_SHAPE_MENU_OPTIONS = 8;
	static const int BEGIN_SHAPE_MENU = -1;

	static const int ADD_SHAPE = 0;
	static const int DRAW_SHAPES = 1;
	static const int SELECT_SHAPE = 2;

	static const int CANCEL_SELECTION = 0;
	static const int REMOVE_Shape = 1;
	static const int MOVE_TOP = 2;
	static const int MERGE_SHAPE = 3;
	static const int ADD_ANIMATION = 4;
	static const int DOUBLE_ANIMATION = 5;
	static const int EXIT_OPTION = 7;

	Menu m_app_main_menu;
	Menu m_app_shape_menu;
	ShapesContainer m_shapes;
	Shape*	m_selected_shape;

	ShapesApp()
	: m_selected_shape(NOT_FOUND)
	{
		init();
	}

	void initMainMenu();
	void initShapeMenu();

	void selectShape();
	void runShapeMenu();
	Shape* handleCollision(Shape* firstShape, Shape* secondShape, bool hasCollidedHorizontally);

	void waitForEscape() const;
	void drawShapesWithSelection() const;
	void drawBlinkingPoint(const Point&) const;
	void playAnimation() const;

	void playDoubleAnimation(Shape*);
	bool shouldReturnToShapeMenu(int lastOption) const;

	void moveInScreen(Shape*) const;
};

#endif