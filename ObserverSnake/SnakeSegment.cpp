#include "SnakeSegment.h"

SnakeSegment::SnakeSegment(int x, int y) : Object(x, y) {

}

void SnakeSegment::paint() {
	TextColor(ColorCode_Green);
	gotoXY(_x, _y);
	std::cout << 'O';
}