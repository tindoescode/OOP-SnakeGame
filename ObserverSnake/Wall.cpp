#include "Wall.h"

Wall::Wall(int x, int y) : Object(x, y) { 
	_point = 0; 
}

void Wall::paint() {
	TextColor(ColorCode_Grey);
	gotoXY(_x, _y);

	std::wcout << 'H';
}

int Wall::getPoint() { 
	return _point; 
}