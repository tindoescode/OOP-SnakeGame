#pragma once
#include "Console.h"
#include "Object.h"
#include <iostream>

class SnakeSegment : public Object
{
public:
	SnakeSegment(int x, int y) : Object(x, y) {}
	void paint() {
		TextColor(ColorCode_Green);
		gotoXY(_x, _y);
		std::cout << 'O';
	}
};

