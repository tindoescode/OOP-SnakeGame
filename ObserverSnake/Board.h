#pragma once
#include <vector>
#include <string>
#include <fstream>

#include "Object.h"
#include "SnakeSegment.h"
#include "Snake.h"
#include "Fruit.h"
#include "Wall.h"

class FileNotFoundException : public std::exception {
	const char* what() const noexcept {
		return "File not found";
	}
};

class NoSnakeException : public std::exception {
	const char* what() const noexcept {
		return "No snake position on map";
	}
};

enum class ObjectType {
	snake,
	snake_segment,
	wall,
	fruit
};

class Board {
	friend class Snake;
private:
	int _width;
	int _height;

	std::vector<Object*> objects;
public:
	Board(int width, int height);

	Object* addObject(ObjectType type, int x, int y);
	
	void drawLines();
	void loadMap(std::string path, Snake*& snake);

	bool isOccupied(int x, int y);

	void deleteSnakeSegment(int x, int y);
	void deleteFruit(int x, int y);
	int getWidth();
	int getHeight();
};

