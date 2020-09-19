#pragma once
#include <deque>
#include "SnakeSegment.h"
#include "Gate.h"
#include "Item.h"

class SceneGame;
class Fruit;
class Wall;
class SceneSaveGame;
class Gift;

const int ITEM_MAXSLOT = 3;

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
	bool _dead;

	Direction _direction;
	std::deque<std::shared_ptr<SnakeSegment>> segments;
	std::shared_ptr<SceneGame> _board;
	std::shared_ptr<Item> items[ITEM_MAXSLOT];
public:
	Snake(int x, int y, std::shared_ptr<SceneGame> board);

	void setPos(int x, int y);
	void setDead();

	GateCollisionType gateCollision(unsigned int score);
	bool bodyCollision();
	
	std::shared_ptr<Fruit> fruitCollision();
	std::shared_ptr<Gift> giftCollision();
	std::shared_ptr<Wall> wallCollision();

	void eatFruit(std::shared_ptr<Fruit> destinateFruit);
	bool getItem(std::shared_ptr<Gift> gift);
	void turnHead(Direction direction);

	void move();
	
	// Enlonger n segments
	void enlonger(int n);

	void paint();
	bool isdead();
};

