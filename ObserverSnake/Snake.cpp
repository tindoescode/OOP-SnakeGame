#include "Snake.h"
#include "SceneGame.h"
#include "Wall.h"

Snake::Snake(int x, int y, SceneGame* board) : Object(x, y) {
	_direction = Direction::idle;
	_dead = false;
	_board = board;

	// Initialize with a segment (assume it is snake's head)
	segments.push_back(dynamic_cast<SnakeSegment*>(_board->addObject(ObjectType::snake_segment, x, y)));
}

void Snake::setPos(int x, int y) {
	segments.front()->setPos(x, y);
}

void Snake::setDead() { 
	_dead = true; 
}

bool Snake::bodyCollision() {
	for (auto i = segments.begin() + 1; i != segments.end(); i++)
	{
		if (_x == (*i)->getX() && _y == (*i)->getY()) {
			return true;
		}
	}
	return false;
}

Fruit* Snake::matchFruit() {
	for (auto i : _board->objects) {
		if (dynamic_cast<Fruit*>(i)) {
			if (i->getX() == _x && i->getY() == _y) return dynamic_cast<Fruit*>(i);
		}
	}
	return nullptr;
}

Wall* Snake::wallCollision() {
	for (auto i : _board->objects) {
		if (dynamic_cast<Wall*>(i)) {
			if (i->getX() == _x && i->getY() == _y) return dynamic_cast<Wall*>(i);
		}
	}
	return nullptr;
}

void Snake::eatFruit(Fruit* destinateFruit) {
	const int x = destinateFruit->getX(), y = destinateFruit->getY();

	// Remove fruit
	_board->deleteFruit(x, y);

	// The size is automatically add on the next move.
	auto object = dynamic_cast<SnakeSegment*>(_board->addObject(ObjectType::snake_segment, -1, -1));
	segments.push_back(object);

	auto [X, Y] = _board->getFreeBlock();

	Fruit* fruit = dynamic_cast<Fruit*>(_board->addObject(ObjectType::fruit, X, Y));
	fruit->paint();
}

void Snake::turnHead(Direction direction) {
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

	if(!(direction != Direction::down && direction != Direction::up && direction != Direction::left && direction != Direction::right))
		_direction = direction;
}

void Snake::move() {
	if (_direction == Direction::idle) return;
	//new head
	int x = segments.front()->getX(), y = segments.front()->getY();

	switch (_direction) {
	case Direction::up: {
		y--;
		break;
	}
	case Direction::down: {
		y++;
		break;
	}
	case Direction::left: {
		x--;
		break;
	}
	case Direction::right: {
		x++;
		break;
	}	
	}
	
	// if _snake get over border
	if (x > _board->_position.X + _board->_width) {
		x = _board->_position.X;
	}
	else if (x < _board->_position.X) {
		x = _board->_position.X + _board->_width;
	}
	else if (y > _board->_position.Y + _board->_height) {
		y = _board->_position.Y;
	}
	else if (y < _board->_position.Y) {
		y = _board->_position.Y + _board->_height;
	}

	// Add new head object
	auto object = dynamic_cast<SnakeSegment*>(_board->addObject(ObjectType::snake_segment, x, y));
	segments.push_front(object);

	// Update new head position
	_x = x;
	_y = y;

	// Delete tail object / old head object if its size was 1
	x = segments.back()->getX(), y = segments.back()->getY();
	
	_board->deleteSnakeSegment(x, y);
	segments.pop_back();
}

void Snake::paint() {
	TextColor(ColorCode_Green);

	if(segments.front()->getX() != 0 && segments.front()->getY() != 0)
		segments.front()->paint();
}

bool Snake::isdead() { 
	return _dead; 
}
