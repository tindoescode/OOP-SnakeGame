#pragma once
#include "Console.h"
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <conio.h>

#define MAUNEN 176
#define MAUCHU 14

class Scene;

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
	Menu(const std::vector<std::wstring> items, std::function<void(unsigned int listitem)> onItemSelected);
	~Menu();

	void Draw();
	
	void ProcessInput();
	void OnActivate();
	void OnDeactivate();
	void Update(Status key);

	void Title();

	//MenuBoder
	int maxLength(std::vector<std::wstring> item);
	void menuBorder(int maxLenght, int maxHeight);
protected:
	// Called when item selected
	std::function<void(unsigned int listitem)> OnItemSelected;

	std::vector<std::wstring> _items;

	int _selectedItem;
	int* color;
};