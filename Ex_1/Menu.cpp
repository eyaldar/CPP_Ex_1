#include <iostream>
using namespace std;

#include "menu.h"
#include "gotoxy.h"

Menu::Menu(const Menu& menu)
{
	init(menu.m_num_of_options);

	for (unsigned int i = 0; i < m_num_of_options; i++)
	{
		this->set(i, menu.m_options_text[i]);
		this->setAvailability(i, menu.m_option_availability[i]);
	}
}

Menu::~Menu()
{
	clearMenu();
}

void Menu::clearMenu()
{
	delete []m_options_text;
	m_options_text = NULL;

	delete []m_option_availability;
	m_option_availability = NULL;

	m_num_of_available_options = 0;
	m_num_of_options = 0;
}

void Menu::setAvailability(unsigned int option_number, bool isEnabled)
{
	if(m_option_availability[option_number] != isEnabled)
	{
		if(isEnabled)
			m_num_of_available_options++;
		else
			m_num_of_available_options--;
	}

	m_option_availability[option_number] = isEnabled;
}

void Menu::displayOptions()
{
	for (unsigned int i=0; i < m_num_of_options; i++)
	{
		if(m_option_availability[i])
		{
			cout << i << "> " << m_options_text[i] << endl;
		}
	}

	cout << "Please enter your choice:";
}

void Menu::init(unsigned int num_of_options)
{
	clearMenu();

	m_num_of_options = num_of_options;
	m_options_text = new string [num_of_options];
	m_option_availability = new bool [num_of_options];
}


void Menu::set(unsigned int option_number, string option_text)
{
	setAvailability(option_number, true);

	m_options_text[option_number] = option_text;
}

unsigned int Menu::choose()
{
	unsigned int l_choice = m_num_of_options;

	clrscr();
	displayOptions();
	cin >> l_choice;

	while (l_choice >= m_num_of_options && m_num_of_available_options > 0)
	{
		cerr << "Wrong option ! Please choose an option between 0 and " 
			 << m_num_of_options << endl << endl << endl;
		displayOptions();

		cin >> l_choice;
	}

	return l_choice;
}
