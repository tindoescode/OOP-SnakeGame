#include "Game.h"

#include <iostream>
#include <ctime>
#include <conio.h>

#include <io.h>
#include <fcntl.h>
#include <clocale>

int main() {
	// Create time seed
	srand(static_cast<unsigned int>(time(0)));

	// Set console size
	SetWindow(SCREEN_WIDTH, SCREEN_HEIGHT);

	Nocursortype();

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