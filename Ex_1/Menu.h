#ifndef __MENU_H__
#define __MENU_H__

#include <string>
#include <iostream>
#include "Gotoxy.h"

class Menu
{
public:
	Menu()
	:m_num_of_options(0), m_option_availability(NULL), m_options_text(NULL), m_num_of_available_options(0) {}
	Menu(const Menu&);
	~Menu();

	void init(unsigned int num_of_options);
	void set(unsigned int option_number, std::string option_text);
	void setAvailability(unsigned int option_number, bool isEnabled);
	unsigned int choose();
private:
	unsigned int m_num_of_options;
	unsigned int m_num_of_available_options;
	bool *m_option_availability;
	std::string *m_options_text;

	void displayOptions();
	void clearMenu();
	void checkAvailableOptions();
};

#endif