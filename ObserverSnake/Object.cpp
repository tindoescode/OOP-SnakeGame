#include "Object.h"


Object::Object(int x, int y) : _x(x), _y(y) {};

Object::~Object() {
	gotoXY(_x, _y);
	std::cout << " ";
}

int Object::getX() { 
	return _x; 
}

int Object::getY() { 
	return _y; 
}

void Object::setPos(int x, int y) {
	_x = x;
	_y = y;
}
