#include "Board.h"

Board::Board(int width, int height) : _width(width), _height(height) {
	Nocursortype();
}

Object* Board::addObject(ObjectType type, int x, int y) {
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
		object = new Wall(x, y);
	}
	objects.push_back(object);

	return object;
}

void Board::drawLines() {
	int xPos, yPos;
	//it will be changed when we have more information 
	//draw line at the top of program
	xPos = 0, yPos = 0;
	while (xPos <= 100) {
		gotoXY(xPos, yPos);
		std::cout << "+";
		xPos++;
	}

	//draw line at the bottom of program
	xPos = 0, yPos = 30;
	while (xPos <= 100) {
		gotoXY(xPos, yPos);
		std::cout << "+";
		xPos++;
	}

	//draw line at the left of program
	xPos = 0, yPos = 0;
	while (yPos <= 30) {
		gotoXY(xPos, yPos);
		std::cout << "+";
		yPos++;
	}

	//draw line at the right of program
	xPos = 100, yPos = 0;
	while (yPos <= 30) {
		gotoXY(xPos, yPos);
		std::cout << "+";
		yPos++;
	}
}

void Board::loadMap(std::string path, Snake*& snake) {
	std::ifstream f;

	f.open(path, std::ios::in);

	//TODO: make it library
	try {
		if (!f.is_open()) throw FileNotFoundException();
	}
	catch (std::exception& ex) {
		system("cls");
		std::cout << ex.what();
	}
	
	std::string line;
	int h = 0;
	while (std::getline(f, line)) 
	{
		for (size_t i = 0; i < line.length(); i++) 
		{
			if (line[i] == 'i') // wall
			{
				addObject(ObjectType::wall, i, h);
			}
			else if (line[i] == '>') // start
			{
				snake = dynamic_cast<Snake*>(addObject(ObjectType::snake, i, h));
			}
		}
		h++;
	}

	// set width, height
	_width = 100;
	_height = 30;

	for (auto i : objects) {
		i->paint();
	}

	try {
		if (!snake) throw NoSnakeException();
	}
	catch (std::exception& ex) {
		system("cls");
		std::cout << ex.what();
	}

	f.close();
}

bool Board::isOccupied(int x, int y) {
	for (auto i : objects) {
		if (i->getX() == x && i->getY() == y) return true;
	}
	return false;
}

void Board::deleteSnakeSegment(int x, int y) {
	for (auto i = objects.begin(); i != objects.end(); i++) {
		if ((*i)->getX() == x && (*i)->getY() == y && dynamic_cast<SnakeSegment*>(*i)) {
			delete* i;
			objects.erase(i);
			break;
		}
	}
}

void Board::deleteFruit(int x, int y) {
	for (auto i = objects.begin(); i != objects.end(); i++) {
		if ((*i)->getX() == x && (*i)->getY() == y && dynamic_cast<Fruit*>(*i)) {
			delete* i;
			objects.erase(i);
			break;
		}
	}
}

int Board::getWidth() { 
	return _width; 
}

int Board::getHeight() { 
	return _height; 
}
