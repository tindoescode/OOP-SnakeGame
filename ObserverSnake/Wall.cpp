#include "Wall.h"

Wall::Wall(int x, int y) : Object(x, y) { 
	_point = 0; 
}

void Wall::paint() {
	TextColor(ColorCode_DarkCyan);
	gotoXY(_x, _y);
	std::cout << 'i';
}

int Wall::getPoint() { 
	return _point; 
}