#include "Gate.h"

Gate::Gate(int x, int y) : Object(x, y) {
	_point = 0;
}

void Gate::paint() {
	TextColor(ColorCode_Red);
	gotoXY(_x, _y - 1);
	std::cout << char(220) << char(220) << char(220);
	gotoXY(_x, _y);
	std::cout << char(219);
	gotoXY(_x, _y + 1);
	std::cout << char(223) << char(223) << char(223);
}

int Gate::getPoint() {
	return _point;
}