#include <iostream>
using namespace std;

#include "menu.h"
#include "gotoxy.h"

Menu::Menu(const Menu& menu)
{
	Init(menu.m_num_of_options);

	for (unsigned int i = 0; i < m_num_of_options; i++)
	{
		this->set(i, menu.m_options_text[i]);
	}
}

Menu::~Menu()
{
	clearMenu();
}

void Menu::clearMenu()
{
	if(m_options_text != NULL)
	{
		delete []m_options_text;
		delete []m_options_text;
		m_options_text = NULL;
		m_usableOptions = 0;
	}
}

void Menu::updateUsability(unsigned int option_number, const string& option_text)
{
	if(option_text.empty() && !m_options_text[option_number].empty())
	{
		m_usableOptions--;
	}
	else if(!option_text.empty() && m_options_text[option_number].empty())
	{
		m_usableOptions++;
	}
}

void Menu::displayOptions()
{
	for (unsigned int i=0; i < m_num_of_options; i++)
	{
		if(!m_options_text[i].empty())
		{
			cout << i << "> " << m_options_text[i] << endl;
		}
	}
}

void Menu::Init(unsigned int num_of_options)
{
	clearMenu();
	m_usableOptions = 0;

	m_num_of_options = num_of_options;
	m_options_text = new string [num_of_options];
}


void Menu::set(unsigned int option_number, string option_text)
{
	updateUsability(option_number, option_text);

	m_options_text[option_number] = option_text;
}

unsigned int Menu::choose()
{
	unsigned int l_choice = m_num_of_options;

	clrscr();
	displayOptions();
	cin >> l_choice;
	while (l_choice >= m_num_of_options)
	{
		cerr << "Wrong option ! Please choose an option between 0 and " 
			 << m_num_of_options << endl << endl << endl;
		displayOptions();

		cin >> l_choice;
	}

	return l_choice;
}
