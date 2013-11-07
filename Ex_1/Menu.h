#ifndef __MENU_H__
#define __MENU_H__

#include <string>

class Menu
{
public:
	Menu()
	:m_num_of_options(0), m_usableOptions(0), m_options_text(NULL) {}
	Menu(const Menu&);
	~Menu();

	void Init(unsigned int num_of_options);
	void set(unsigned int option_number, std::string option_text);
	unsigned int choose();
private:
	unsigned int m_num_of_options;
	unsigned int m_usableOptions;
	std::string *m_options_text;

	void updateUsability(unsigned int option_number, const std::string& option_text);
	void displayOptions();
	void clearMenu();
};

#endif