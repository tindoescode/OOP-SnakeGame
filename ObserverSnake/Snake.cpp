#include "Snake.h"
#include "SceneGame.h"
#include "Wall.h"
#include "Gate.h"
#include "Gift.h"

Snake::Snake(int x, int y, std::shared_ptr<SceneGame> board) : Object(x, y) {
	_direction = Direction::idle;
	_dead = false;
	_board = board;

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
	int i = 0;

	while (items[i]) {
		// Can't find a free slot
		if (i >= ITEM_MAXSLOT) return false;
		i++;
	}

	// found a slot
	//if (!items[i]) items[i] = std::make_shared<Gift>();

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
