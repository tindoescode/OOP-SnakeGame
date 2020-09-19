#include "Gift.h"

Gift::Gift(int x, int y) : Object(x, y) {}

void Gift::paint() {
	TextColor(ColorCode_Cyan);
	gotoXY(_x, _y);
	std::cout << '?';
}
