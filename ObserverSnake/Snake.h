#pragma once
#include <deque>
#include "SnakeSegment.h"

class Board;
class Fruit;
class Wall;

enum class Direction {
	idle = NULL,
	up = 'w',
	down = 's',
	left = 'a',
	right = 'd'
};

class Snake : public Object
{
private:
	Direction _direction;
	std::deque<SnakeSegment*> segments;
	bool _dead;
	Board* _board;

public:
	Snake(int x, int y, Board* board);
	void setPos(int x, int y) {
		segments.front()->setPos(x, y);
	}
	void setDead() { _dead = true; }
	bool bodyCollision() 
	{
		for (auto i = segments.begin() + 1; i != segments.end(); i++) 
		{
			if (_x == (*i)->getX() && _y == (*i)->getY()) {
				return true;
			}
		}
		return false;
	}
	Fruit* matchFruit();
	Wall* wallCollision();
	void eatFruit(Fruit* destinateFruit);
	void turnHead(Direction direction) 
	{
		if (direction == Direction::down && _direction == Direction::up) {
			return;
		}
		if (direction == Direction::up && _direction == Direction::down) {
			return;
		}
		if (direction == Direction::left && _direction == Direction::right) {
			return;
		}
		if (direction == Direction::right && _direction == Direction::left) {
			return;
		}

		_direction = direction;
	}
	void move();
	void paint() 
	{
		TextColor(ColorCode_Green);

		segments.front()->paint();
	}
	bool isdead() { return _dead; }
};

