#include "Menu.h"
#include "Game.h"
#include <functional>

Menu::~Menu() {
	if (color) delete color;
}
void Menu::Draw()
{
	Title();
	menuBorder();
	for (int i = 0; i < heightBorder; i++)
	{
		Console::TextColor(color[i]);
		Console::gotoXY(SCREEN_WIDTH / 2 - lengthBorder / 2, SCREEN_HEIGHT / 2 - heightBorder / 2 + i);
		std::wcout << _items[i] << std::endl;
	}
}

Menu::Menu(const std::vector<std::wstring> items, std::function<void(unsigned int listitem)> onItemSelected) 
	: _selectedItem(0), OnItemSelected(onItemSelected) {
	
	_items = items;

	//set max length and height
	int maxLength = 0;
	for (int i = 0; i < items.size(); i++) {
		if (items[i].size() > maxLength)	maxLength = (unsigned int)items[i].size();
	}
	lengthBorder = maxLength;
	heightBorder = (int)items.size();

	//Console::clrscr();

	color = new int[ _items.size() ];

	// ?
	for (int i = 0; i < _items.size(); i++)	color[i] = (unsigned int)MAUCHU;
	color[0] = MAUNEN;
}

void Menu::ProcessInput() {
	int key = _getch();

	Update(Status(key));
}

void Menu::OnActivate()
{
	Draw();
}

void Menu::OnDeactivate()
{
	system("cls");
}

void Menu::Update(Status key) {
	if ((int) key == 224) key = Status(_getch());
	
	switch (key)
	{
	case Status::up: {
		_selectedItem = (_selectedItem == 0) ? unsigned int (_items.size() - 1) : unsigned int(_selectedItem - 1);

		break;
	}

	case Status::down: {
		_selectedItem = (_selectedItem == _items.size() - 1) ? 0 : _selectedItem + 1;

		break;
	}

	case Status::enter: {
		Console::gotoXY(0, _selectedItem + 10);
		Console::TextColor(ColorCode_Black);

		//cls khong clear dc mau nen` 
		std::cout << "\t\t\t\t\t\t\t\t\t\t";

		OnItemSelected(_selectedItem);
		return;
	}
	}

	// Init color
	for (int i = 0; i < _items.size(); i++)
	{
		color[i] = MAUCHU;
	}
	color[_selectedItem] = MAUNEN;

	Draw();
}

void Menu::Title() {
	Console::gotoXY(0, 0);
	Console::TextColor(rand() % 10 + 1);

	std::cout << "\
 				  .-')        .-') _    ('-.    .-. .-')     ('-.   \n\
 				  ( OO ).     ( OO ) )  ( OO ).-.\  ( OO )  _(  OO)  \n\
 				  (_)---\\_),--./ ,--,'   / . --. /,--. ,--. (,------. \n\
 				  /    _ | |   \\ |  |\\   | \\-.  \\ |  .'   /  |  .---' \n\
 				  \\  :` `. |    \\|  | ).-'-'  |  ||      /,  |  |     \n\
 				   '..`''.)|  .     |/  \\| |_.'  ||     ' _)(|  '--.  \n";
	std::cout << "\
				  .-._)   \\|  |\\    |    |  .-.  ||  .   \\   |  .--'  \n\
				  \\       /|  | \\   |    |  | |  ||  |\\   \\  |  `---. \n\
				  `-----' `--'  `--'    `--' `--'`--' '--'  `------' \n\
	";
}


void Menu::menuBorder() {
	//top and bottom border
	Console::TextColor(ColorCode_Cyan);
	for (int i = SCREEN_WIDTH / 2 - lengthBorder / 2 - 2; i <= SCREEN_WIDTH / 2 + lengthBorder / 2 + 2; i++) {
		Console::gotoXY(i, SCREEN_HEIGHT / 2 - heightBorder / 2 - 2);
		std::cout << (char)205;
		Console::gotoXY(i, SCREEN_HEIGHT / 2 + heightBorder / 2 + 2);
		std::cout << (char)205;
	}

	{	//4 corner
		Console::gotoXY(SCREEN_WIDTH / 2 - lengthBorder / 2 - 2, SCREEN_HEIGHT / 2 - heightBorder / 2 - 2);
		std::cout << (char)201;
		Console::gotoXY(SCREEN_WIDTH / 2 - lengthBorder / 2 - 2, SCREEN_HEIGHT / 2 + heightBorder / 2 + 2);
		std::cout << (char)200;

		Console::gotoXY(SCREEN_WIDTH / 2 + lengthBorder / 2 + 2, SCREEN_HEIGHT / 2 - heightBorder / 2 - 2);
		std::cout << (char)187;
		Console::gotoXY(SCREEN_WIDTH / 2 + lengthBorder / 2 + 2, SCREEN_HEIGHT / 2 + heightBorder / 2 + 2);
		std::cout << (char)188;
	}
	//left and right border
	for (int i = SCREEN_HEIGHT / 2 - heightBorder / 2 - 1; i <= SCREEN_HEIGHT / 2 + heightBorder / 2 + 1; i++) {
		Console::gotoXY(SCREEN_WIDTH / 2 - lengthBorder / 2 - 2, i);
		std::cout << (char)186;
		Console::gotoXY(SCREEN_WIDTH / 2 + lengthBorder / 2 + 2, i);
		std::cout << (char)186;
	}
}