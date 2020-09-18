#pragma once
#include <iostream>
#include "Console.h"

class Object {
protected:
	int _x;
	int _y;
public:
	Object(int x, int y);
	virtual ~Object();

	int getX();
	int getY();

	void setPos(int x, int y);

	virtual void paint() = 0;
};

