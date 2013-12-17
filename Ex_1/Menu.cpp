#include "menu.h"

using namespace std;

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

void Menu::displayOptions() const
{
	for (unsigned int i=0; i < m_num_of_options; i++)
	{
		if(m_option_availability[i])
		{
			cout << i + 1 << "> " << m_options_text[i] << endl;
		}
	}

	cout << "Please enter your choice:";
}

void Menu::init(unsigned int num_of_options)
{
	clearMenu();

	m_num_of_options = num_of_options;
	m_options_text = new string [num_of_options];
	m_option_availability = new bool [num_of_options]();
}


void Menu::set(unsigned int option_number, string option_text)
{
	setAvailability(option_number, true);

	m_options_text[option_number] = option_text;
}

const char* Menu::get(unsigned int option_number) const
{
	return m_options_text[option_number].c_str();
}

void Menu::checkAvailableOptions() const
{
	if(m_num_of_available_options <= 0)
		throw "Error! there are no available options to choose from...";
}

unsigned int Menu::choose() const
{
	checkAvailableOptions();

	unsigned int l_choice = m_num_of_options;

	clrscr();
	displayOptions();
	cin >> l_choice;

	l_choice--;

	while (l_choice < 0 || l_choice >= m_num_of_options || !m_option_availability[l_choice])
	{
		cerr << "Wrong option ! Please choose an option from the available options." << endl << endl << endl;
		displayOptions();

		cin >> l_choice;
		l_choice--;
	}

	return l_choice;
}
