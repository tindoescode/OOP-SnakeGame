#pragma once
#include "Console.h"
#include "Object.h"
#include <iostream>

class Fruit : public Object
{
private:
	int _point;
public:
	Fruit(int x, int y) : Object(x, y) { _point = 0; }
	void paint() {
		TextColor(ColorCode_Red);
		gotoXY(_x, _y);
		std::cout << '#';
	}
	int getPoint() { return _point;  }
};

