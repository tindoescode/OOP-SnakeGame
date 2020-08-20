#include "Snake.h"
#include "Board.h"

Snake::Snake(int x, int y, Board* board) : Object(x, y) {
	_direction = Direction::idle;
	_dead = false;
	_board = board;

	// Initialize with a segment (assume it is snake's head)
	segments.push_back(dynamic_cast<SnakeSegment*>(_board->addObject(ObjectType::snake_segment, x, y)));
};

void Snake::move()
{
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
	default: {
		return;
	}
	}
	
	// Add new head object
	auto object = dynamic_cast<SnakeSegment*>(_board->addObject(ObjectType::snake_segment, x, y));
	segments.push_front(object);

	// Update new head position
	_x = x;
	_y = y;

	// Delete tail object / old head object if its size was 1
	x = segments.back()->getX(), y = segments.back()->getY();
	
	_board->deleteObject(x, y);
	segments.pop_back();
}

bool Snake::matchFruit() {
	for (auto i : _board->objects) {
		if (dynamic_cast<Fruit*>(i)) {
			if (i->getX() == _x && i->getY() == _y) return true;
		}
	}
	return false;
}