#include "Menu.h"

Menu::~Menu() {
	if (color) delete color;
}
void Menu::Draw()
{
	for (int i = 0; i < _items.size(); i++)
	{
		TextColor(color[i]);
		gotoXY(30, 10 + i);
		std::cout << i + 1 << ") " << _items[i] << std::endl;
	}
}
Menu::Menu(const std::vector<std::string> items) : _selectedItem(0) {
	_items = items;

	clrscr();

	color = new int[ _items.size() ];

	// ?
	for (int i = 0; i < _items.size(); i++)	color[i] = MAUCHU;
	color[0] = MAUNEN;

	Draw();
}

void Menu::ProcessInput() {
	int key = _getch();

	Update(Status(key));
}

void Menu::OnDeactivate()
{
	clrscr;
}

void Menu::Update(Status key) {
	if ((int)key == 224) key = Status(_getch());
	
	switch (key)
	{
	case Status::up: {
		_selectedItem = (_selectedItem == 0) ? _items.size() - 1 : _selectedItem - 1;

		break;
	}

	case Status::down: {
		_selectedItem = (_selectedItem == _items.size() - 1) ? 0 : _selectedItem + 1;

		break;
	}

	case Status::enter: {
		gotoXY(0, _selectedItem + 10);
		TextColor(ColorCode_Back);

		//cls khong clear dc mau nen` 
		std::cout << "\t\t\t\t\t\t\t\t\t\t";

		OnItemSelected(_selectedItem);
		//return choose;
	}
	}

	// ?
	for (int i = 0; i < _items.size(); i++)
	{
		color[i] = MAUCHU;
	}
	color[_selectedItem] = MAUNEN;

	Draw();
}