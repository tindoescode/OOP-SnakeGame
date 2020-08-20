#pragma once
#include <vector>
#include "Object.h"
#include "SnakeSegment.h"
#include "Snake.h"
#include "Fruit.h"

enum class ObjectType {
	snake,
	snake_segment,
	wall,
	fruit
};

class Board
{
friend class Snake;
private:
	int _width;
	int _height;

	std::vector<Object*> objects;
public:
	Board(int width, int height) : _width(width), _height(height) {
		Nocursortype();
	}

	Object* addObject(ObjectType type, int x, int y) {
		Object* object;

		if (type == ObjectType::snake) {
			object = new Snake(x, y, this);
		}
		else if (type == ObjectType::snake_segment) {
			object = new SnakeSegment(x, y);
		}
		else if (type == ObjectType::fruit) {
			object = new Fruit(x, y);
		}
		else if (type == ObjectType::wall) {
			//objects.push_back(dynamic_cast<Object*>(new Wall()));
		}
		objects.push_back(object);

		return object;
	}

	void deleteObject(int x, int y) {
		for (auto i = objects.begin(); i != objects.end(); i++) {
			if ((*i)->getX() == x && (*i)->getY() == y) {
				delete* i;
				objects.erase(i);
				break;
			}
		}
	}
	void deleteFruit(int x, int y) {
		for (auto i = objects.begin(); i != objects.end(); i++) {
			if ((*i)->getX() == x && (*i)->getY() == y && dynamic_cast<Fruit*>(*i)) {
				delete* i;
				objects.erase(i);
				break;
			}
		}
	}
	int getWidth() { return _width; }
	int getHeight() { return _height; }
};

