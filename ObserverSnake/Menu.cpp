#include "Menu.h"
#include <functional>

Menu::~Menu() {
	if (color) delete color;
}
void Menu::Draw()
{
	Title();
	menuBorder(maxLenght(_items), _items.size());
	for (int i = 0; i < _items.size(); i++)
	{
		TextColor(color[i]);
		gotoXY(40, 15 + i);
		std::wcout << _items[i] << std::endl;
	}
}

Menu::Menu(const std::vector<std::wstring> items, std::function<void(unsigned int listitem)> onItemSelected) 
	: _selectedItem(0), OnItemSelected(onItemSelected) {
	_items = items;

	//clrscr();

	color = new int[ _items.size() ];

	// ?
	for (int i = 0; i < _items.size(); i++)	color[i] = MAUCHU;
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
		gotoXY(0, _selectedItem + 10);
		TextColor(ColorCode_Black);

		//cls khong clear dc mau nen` 
		std::wcout << L"\t\t\t\t\t\t\t\t\t\t";

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


void Menu::letterS(int x, int y) {
	TextColor(9);
	gotoXY(x, y);
	std::wcout << " _____";
	gotoXY(x, y + 1);
	std::wcout << "/  " << (char)254 << "  \\___________ ";
	gotoXY(x, y + 2);
	std::wcout << "\\___              |";
	gotoXY(x, y + 3);
	std::wcout << "|_________    ____|";
	TextColor(12);
	gotoXY(x, y + 4);
	std::wcout << "          \\";
	gotoXY(x, y + 5);
	std::wcout << "           \\____  \\";
	TextColor(14);
	gotoXY(x, y + 6);
	std::wcout << "          |       /";
	gotoXY(x, y + 7);
	std::wcout << "          |______/";
}
void Menu::letterN(int x, int y) {
	TextColor(9);
	gotoXY(x, y);
	std::wcout << "   ___";
	gotoXY(x, y + 1);
	std::wcout << "  |   |/   \\";
	//TextColor(color);
	gotoXY(x, y + 2);
	std::wcout << "  |      ___\\";
	TextColor(12);
	gotoXY(x, y + 3);
	std::wcout << "  |   ___   |";
	gotoXY(x, y + 4);
	std::wcout << "  |   | |   |";
	TextColor(14);
	gotoXY(x, y + 5);
	std::wcout << "  |   | |   |";
	gotoXY(x, y + 6);
	std::wcout << "  |___| |___|";
}
void Menu::letterA(int x, int y) {

	TextColor(9);
	gotoXY(x, y);
	std::wcout << "  _____  __";
	gotoXY(x, y + 1);
	std::wcout << " / __  \\|  \\";
	gotoXY(x, y + 2);
	std::wcout << "|           |";
	TextColor(12);
	gotoXY(x, y + 3);
	std::wcout << "|  " << (char)177 << (char)177 << (char)177 << "    " << (char)177 << " |";
	gotoXY(x, y + 4);
	std::wcout << "|  " << (char)176 << (char)176 << (char)176 << "    " << (char)176 << " |";
	TextColor(14);
	gotoXY(x, y + 5);
	std::wcout << "|       |   |";
	gotoXY(x, y + 6);
	std::wcout << " \\______|___|";
}
void Menu::letterK(int x, int y) {
	TextColor(9);
	gotoXY(x, y);
	std::wcout << " ____    ____";
	gotoXY(x, y + 1);
	std::wcout << "|    |  /   /";
	gotoXY(x, y + 2);
	std::wcout << "|      /   /";
	TextColor(12);
	gotoXY(x, y + 3);
	std::wcout << "|         /";
	gotoXY(x, y + 4);
	std::wcout << "|   |__   \\";
	TextColor(14);
	gotoXY(x, y + 5);
	std::wcout << "|      \\   \\";
	gotoXY(x, y + 6);
	std::wcout << "|____|  \\___\\";
}
void Menu::letterE(int x, int y) {
	TextColor(9);
	gotoXY(x, y);
	std::wcout << "   _______";
	gotoXY(x, y + 1);
	std::wcout << "  /       \\";
	gotoXY(x, y + 2);
	std::wcout << " /  _" << (char)177 << (char)177 << (char)177 << "   \\";
	TextColor(12);
	gotoXY(x, y + 3);
	std::wcout << "|          /";
	gotoXY(x, y + 4);
	std::wcout << "|    _____/_________";
	TextColor(14);
	gotoXY(x, y + 5);
	std::wcout << " \\                  \\";
	gotoXY(x, y + 6);
	std::wcout << "  \\__________________|||||\\__";
}
void Menu::Title() {
	int x = 10;
	int y = 1;
	letterS(x - 10, y - 1);
	letterN(x + 10, y);
	letterA(x + 25, y);
	letterK(x + 40, y);
	letterE(x + 55, y);
}

int Menu::maxLenght(std::vector<std::wstring> item) {
	int max = 0;
	for (int i = 0; i < item.size(); i++) {
		if (item[i].size() > max)	max = item[i].size();
	}
	return max;
}
void Menu::menuBorder(int maxLenght, int maxHeight) {
	//top and bottom border
	TextColor(ColorCode_Cyan);
	for (int i = 36; i < maxLenght + 45; i++) {
		gotoXY(i, 13);
		std::wcout << (char)205;
		gotoXY(i, maxHeight + 17);
		std::wcout << (char)205;
	}

	{	//4 corner
		gotoXY(35, 13);
		std::wcout << (char)201;
		gotoXY(35, maxHeight + 17);
		std::wcout << (char)200;

		gotoXY(maxLenght + 45, 13);
		std::wcout << (char)187;
		gotoXY(maxLenght + 45, maxHeight + 17);
		std::wcout << (char)188;
	}
	//left and right border
	for (int i = 14; i < maxHeight + 17; i++) {
		gotoXY(35, i);
		std::wcout << (char)186;
		gotoXY(maxLenght + 45, i);
		std::wcout << (char)186;
	}
}