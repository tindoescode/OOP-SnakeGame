#include "Gate.h"

Gate::Gate(int x, int y) : Object(x, y) {
	_point = 0;
}

void Gate::paint() {
	TextColor(ColorCode_Red);
	gotoXY(_x, _y);
	std::wcout << L'\u0663' << L'\u8766';
}

int Gate::getPoint() {
	return _point;
}