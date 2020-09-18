#include "Game.h"

#include <iostream>
#include <ctime>
#include <conio.h>

#include <io.h>
#include <fcntl.h>

int main() {
	//TODO: Make creatory factory for each object
	_setmode(_fileno(stdout), _O_U16TEXT);

	// Create time seed
	srand(static_cast<unsigned int>(time(0)));

	// Set console size
	SetWindow(120, 30 + 1);

	//TextColor(ColorCode_Cyan);
	//gotoXY(0, 0);
	//std::wcout << L"\x223E" << std::endl;

	// Make the game loop
	Game game;
	while (game.IsRunning()) {
		game.ProcessInput();
		game.Update();
		game.LateUpdate();
		game.Draw();
	}

	return 0;
}