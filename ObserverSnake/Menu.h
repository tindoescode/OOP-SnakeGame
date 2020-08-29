#pragma once
#include "Console.h"
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

#define MAUNEN 176
#define MAUCHU 14

enum class Status {
	up = 72,
	down = 80,
	//TODO: handle left/right navigate
	left = 75,
	right = 77,
	enter = 13,
	back
};

class Menu {
public:
	Menu(const std::vector<std::string> items);
	~Menu();
	void Draw();
	void ProcessInput();
	void OnDeactivate();

	void Update(Status key);

	// Called when item selected
	virtual void OnItemSelected(int listitem) = 0;

protected:
	std::vector<std::string> _items;

	int _selectedItem;
	int* color;
};