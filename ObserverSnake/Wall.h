#pragma once
#include "Console.h"
#include "Object.h"

class Wall : public Object
{
private:
	int _point;
public:
	Wall(int x, int y) : Object(x, y) { _point = 0; }
	void paint() {
		TextColor(ColorCode_DarkCyan);
		gotoXY(_x, _y);
		std::cout << 'i';
	}
	int getPoint() { return _point; }
};

