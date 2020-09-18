#include "Fruit.h"

Fruit::Fruit(int x, int y) : Object(x, y) {
	_point = 0; 
}

void Fruit::paint() {
	TextColor(ColorCode_Red);
	gotoXY(_x, _y);
	std::wcout << L'#';
}

int Fruit::getPoint() { 
	return _point; 
}