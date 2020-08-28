#pragma once
#include <deque>
#include "SnakeSegment.h"

class SceneGame;
class Fruit;
class Wall;

enum class Direction {
	idle = NULL,
	up = 'w',
	down = 's',
	left = 'a',
	right = 'd'
};

class Snake : public Object {
private:
	Direction _direction;
	std::deque<SnakeSegment*> segments;
	bool _dead;
	SceneGame* _board;

public:
	Snake(int x, int y, SceneGame* board);
	void setPos(int x, int y);
	void setDead();
	bool bodyCollision();
	Fruit* matchFruit();
	Wall* wallCollision();
	void eatFruit(Fruit* destinateFruit);
	void turnHead(Direction direction);
	void move();
	void paint();
	bool isdead();
};

