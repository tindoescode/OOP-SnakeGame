#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <conio.h>

#include "Object.h"
#include "SnakeSegment.h"
#include "Snake.h"
#include "Fruit.h"
#include "Wall.h"

#include "Scene.h"

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

class SceneGame : public Scene {
	friend class Snake;
private:
	int _width;
	int _height;

	std::string _mapPath;
	std::vector<Object*> objects;

	Snake* _snake;
	Fruit* _fruit;
public:
	SceneGame();
	SceneGame(std::string mapPath);

	void OnCreate() override;
	void OnDestroy() override;

	void OnActivate() override;
	void OnDeactivate() override;
	void ProcessInput() override;
	void Update() override;
	void LateUpdate() override;
	COORD getFreeBlock();
	void Draw() override;

	Object* addObject(ObjectType type, size_t x, size_t y);
	void drawBorder();
	void loadMap(std::string path, Snake*& snake);

	bool isOccupied(int x, int y);

	void deleteSnakeSegment(int x, int y);
	void deleteFruit(int x, int y);

	int getWidth();
	int getHeight();
};