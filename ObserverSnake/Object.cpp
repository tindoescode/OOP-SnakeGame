#include "Object.h"

Object::Object(int x, int y) : _x(x), _y(y), _width(1), _height(1) {};

Object::~Object() {
	if (_x != -1 && _y != -1) {
		gotoXY(_x, _y);
		std::wcout << " ";
	}
}

int Object::getWidth() { return _width; }
int Object::getHeight() { return _height; }

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
