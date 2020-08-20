#pragma once
#include <iostream>
#include "Console.h"

class Object
{
protected:
	int _x;
	int _y;
public:
	Object(int x, int y) : _x(x), _y(y) {};
	~Object() {
		gotoXY(_x, _y);
		std::cout << " ";
	}

	int getX() { return _x; }
	int getY() { return _y; }

	void setPos(int x, int y) {
		_x = x;
		_y = y;
	}
	virtual void paint() = 0;
};

