#pragma once
#include "Console.h"
#include "Object.h"
#include <iostream>

class Gate : public Object {
private:
	int _point;
public:
	Gate(int x, int y);
	void paint();
	int getPoint();
};

