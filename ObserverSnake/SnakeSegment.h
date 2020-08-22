#pragma once
#include "Console.h"
#include "Object.h"
#include <iostream>

class SnakeSegment : public Object {
friend class Snake;

public:
	SnakeSegment(int x, int y);
	void paint();
};

