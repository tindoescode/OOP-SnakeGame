#include "Game.h"

#include <iostream>
#include <ctime>
#include <conio.h>

int main() {
	//TODO: Make creatory factory for each object

	// Create time seed
	srand(static_cast<unsigned int>(time(0)));

	Game game;
	while (game.IsRunning()) {
		game.ProcessInput();
		game.Update();
		game.Draw();
	}

	std::cout << "Snake dead." << std::endl;

	return 0;
}