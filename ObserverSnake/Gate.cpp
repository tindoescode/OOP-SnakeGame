#include "Gate.h"

Gate::Gate(int x, int y) : Object(x, y) {
	_point = 0;
	_width = 3;
	_height = 3;
}

void Gate::paint() {
	Console::TextColor(ColorCode_Red);
	Console::gotoXY(_x, _y - 1);
	std::cout << char(220) << char(220) << char(220);
	Console::gotoXY(_x, _y);
	std::cout << char(219);
	Console::gotoXY(_x, _y + 1);
	std::cout << char(223) << char(223) << char(223);
}

int Gate::getPoint() {
	return _point;
}