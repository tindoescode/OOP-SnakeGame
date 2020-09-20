#include "Snake.h"
#include "SceneGame.h"
#include "Wall.h"
#include "Gate.h"
#include "Gift.h"
#include "Rocket.h"
#include "ThroughWall.h"
#include <future>

double Snake::getSpeed() { return _speed; }

bool Snake::isThroughWall() {
	if (_throughWallTime > 0) {
		_throughWallTime -= double(125) / 1000 / _speed;
		return true;
	}
	return false;
}
void Snake::setSpeed(double speed)
{
	_speed = speed;
}

bool Snake::dieInNextStep(const int step, const int score) {
	auto x = _x, y = _y;

	switch (_direction) {
	case Direction::up: {
		y -= step;
		break;
	}
	case Direction::down: {
		y += step;
		break;
	}
	case Direction::left: {
		x -= step;
		break;
	}
	case Direction::right: {
		x += step;
		break;
	}
	}
	
	for (auto i : _board->objects) {
		if (std::dynamic_pointer_cast<Wall>(i) 
			|| std::dynamic_pointer_cast<SnakeSegment>(i) 
			|| gateCollision({(short)x, (short)y}, score) == GateCollisionType::border) {
			if (i->getX() == x && i->getY() == y) return true;
		}
	}
	return false;
}
void Snake::setThroughWall(int time) {
	_throughWallTime += time;
}

Snake::Snake(int x, int y, std::shared_ptr<SceneGame> board) : Object(x, y) {
	_direction = Direction::idle;
	_dead = false;
	_board = board;
	_speed = 1.0;
	_throughWallTime = 0.0;

	// Initialize with a segment (assume it is snake's head)
	segments.push_back(std::dynamic_pointer_cast<SnakeSegment>(_board->addObject(ObjectType::snake_segment, x, y)));
}

void Snake::setPos(int x, int y) {
	segments.front()->setPos(x, y);
}

void Snake::setDead() { 
	_dead = true; 
}

GateCollisionType Snake::gateCollision(unsigned int score) {
	if (score < _board->_currentRound * 100) return GateCollisionType::none;
	for (auto i : _board->objects) {
		if (std::dynamic_pointer_cast<Gate>(i)) {
			if ((i->getX() <= _x && i->getX() + 2 >= _x) && i->getY() - 1 == _y) return GateCollisionType::border; // top
			if ((i->getX() <= _x && i->getX() + 2 >= _x) && i->getY() + 1 == _y) return GateCollisionType::border; // bottom
			if (i->getX() == _x && i->getY() == _y) return GateCollisionType::door;
		}
	}
	return GateCollisionType::none;
}
// Check if in any specify coord that snake can get gate collision
GateCollisionType Snake::gateCollision(COORD coord, unsigned int score) {
	auto [X, Y] = coord;

	if (score < _board->_currentRound * 100) return GateCollisionType::none;
	for (auto i : _board->objects) {
		if (std::dynamic_pointer_cast<Gate>(i)) {
			if ((i->getX() <= X && i->getX() + 2 >= X) && i->getY() - 1 == Y) return GateCollisionType::border; // top
			if ((i->getX() <= X && i->getX() + 2 >= X) && i->getY() + 1 == Y) return GateCollisionType::border; // bottom
			if (i->getX() == X && i->getY() == Y) return GateCollisionType::door;
		}
	}
	return GateCollisionType::none;
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

std::shared_ptr<Fruit> Snake::fruitCollision() {
	for (auto i : _board->objects) {
		if (std::dynamic_pointer_cast<Fruit>(i)) {
			if (i->getX() == _x && i->getY() == _y) return std::dynamic_pointer_cast<Fruit>(i);
		}
	}
	return nullptr;
}

std::shared_ptr<Gift> Snake::giftCollision() {
	for (auto i : _board->objects) {
		if (std::dynamic_pointer_cast<Gift>(i)) {
			if (i->getX() == _x && i->getY() == _y) return std::dynamic_pointer_cast<Gift>(i);
		}
	}
	return nullptr;
}

std::shared_ptr<Wall> Snake::wallCollision() {
	for (auto i : _board->objects) {
		if (std::dynamic_pointer_cast<Wall>(i)) {
			if (i->getX() == _x && i->getY() == _y) return std::dynamic_pointer_cast<Wall>(i);
		}
	}
	return nullptr;
}

void Snake::eatFruit(std::shared_ptr<Fruit> destinateFruit) {
	// Remove fruit
	destinateFruit->setPos(-1, -1); // this avoid destructor to clear new snake segment block
	_board->deleteFruit(-1, -1); // remove fruit with pos -1, -1

	// The size is automatically add on the next move.
	auto object = std::dynamic_pointer_cast<SnakeSegment>(_board->addObject(ObjectType::snake_segment, -1, -1));
	segments.push_back(object);
}

bool Snake::getItem(std::shared_ptr<Gift> gift) {
	int i = 1;

	while (_items[i]) {
		// Can't find a free slot
		if (i >= (ITEM_MAXSLOT + 1)) return false;
		i++;
	}

	// found a slot
	if (!_items[i]) {
		int n = rand() % 2;
		switch (n) {
		case 0:
			_items[i] = std::make_shared<Rocket>();
			std::cout << "You got a \"Rocket 30s\" on slot " << i << ".";
			break;
		case 1:
			_items[i] = std::make_shared<ThroughWall>();
			std::cout << "You got a \"Through Wall 30s\" on slot " << i << ".";
			break;
		}
	}

	return true;
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

void Snake::move(int step) {
	if (_direction == Direction::idle) return;
	//new head
	int x = segments.front()->getX(), y = segments.front()->getY();

	switch (_direction) {
	case Direction::up: {
		y -= step;
		break;
	}
	case Direction::down: {
		y += step;
		break;
	}
	case Direction::left: {
		x -= step;
		break;
	}
	case Direction::right: {
		x += step;
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
	auto head = std::dynamic_pointer_cast<SnakeSegment>(_board->addObject(ObjectType::snake_segment, x, y));
	segments.push_front(head);

	// Update new head position
	_x = x;
	_y = y;

	// Delete tail object / old head object if its size was 1
	x = segments.back()->getX(), y = segments.back()->getY();
	
	_board->deleteSnakeSegment(x, y);
	
	segments.pop_back();
}

std::shared_ptr<SnakeSegment> Snake::getTail() { return segments.back(); }

bool Snake::activeItem(int slot) {
	if (!_items[slot]) return false;
	
	_items[slot]->operate(shared_from_this());

	return true;
}

void Snake::enlonger(int n)
{
	for (int i = 0; i < n; i++) {
		auto segment = std::dynamic_pointer_cast<SnakeSegment>(_board->addObject(ObjectType::snake_segment, -1, -1));
		segments.push_back(segment);
	}
}

void Snake::paint() {
	TextColor(ColorCode_Green);

	if(segments.front()->getX() != 0 && segments.front()->getY() != 0)
		segments.front()->paint();
}

bool Snake::isdead() { 
	return _dead; 
}
