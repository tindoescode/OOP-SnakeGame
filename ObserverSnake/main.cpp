#include "Board.h"
#include "Snake.h"
#include "Fruit.h"
#include <ctime>
#include <conio.h>

int main() {
	// Create time seed
	srand(static_cast<unsigned int>(time(0)));

	// Create objects
	Board* board = new Board(30, 20);
	Snake* snake = dynamic_cast<Snake*>(board->addObject(ObjectType::snake, 10, 10));

	const int randomX = rand() % board->getWidth();
	const int randomY = rand() % board->getHeight();
	Fruit* fruit = dynamic_cast<Fruit*>(board->addObject(ObjectType::fruit, randomX, randomY));
	fruit->paint();

	// Game loop
	char op;
	while (!snake->isdead()) {
		//board->handleKey();
		if (_kbhit())
		{
			op = tolower(_getch());
			snake->turnHead(Direction(op));
		}
		snake->move();

		if (snake->bodyCollision()) {
			snake->setDead();
		}
		/*else if (snake->wallCollision()) {
			snake->setDead();
		}*/
		else if(snake->matchFruit()) {
			snake->eatFruit();
		}
		else if (snake->getX() > board->getWidth()) {
			snake->setPos(0, snake->getY());
		}
		else if (snake->getX() < 0) {
			snake->setPos(board->getWidth(), snake->getY());
		}
		else if (snake->getY() > board->getHeight()) {
			snake->setPos(snake->getX(), 0);
		}
		else if (snake->getY() < 0) {
			snake->setPos(snake->getX(), board->getHeight());
		}

		snake->paint();	

		Sleep(100);
	}

	delete board;
	return 0;
}