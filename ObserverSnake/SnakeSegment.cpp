#include "SnakeSegment.h"

SnakeSegment::SnakeSegment(int x, int y) : Object(x, y) {

}

void SnakeSegment::paint() {
	Console::TextColor(ColorCode_Green);
	Console::gotoXY(_x, _y);
	std::wcout << L'O';
}