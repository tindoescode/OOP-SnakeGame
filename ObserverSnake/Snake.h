#pragma once
#include <deque>
#include "SnakeSegment.h"
#include "Gate.h"

class SceneGame;
class Fruit;
class Wall;
class SceneSaveGame;
enum class Direction {
	idle = NULL,
	up = 'w',
	down = 's',
	left = 'a',
	right = 'd'
};

class Snake : public Object {
	friend class SceneSaveGame;
private:
	Direction _direction;
	std::deque<SnakeSegment*> segments;
	bool _dead;
	SceneGame* _board;

public:
	Snake(int x, int y, SceneGame* board);

	void setPos(int x, int y);
	void setDead();

	GateCollisionType gateCollision(unsigned int score);
	bool bodyCollision();
	Fruit* matchFruit();
	Wall* wallCollision();

	void eatFruit(Fruit* destinateFruit);
	void turnHead(Direction direction);

	void move();
	
	// Enlonger n segments
	void enlonger(int n);

	void paint();
	bool isdead();
};

