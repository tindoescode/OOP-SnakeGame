#include "Board.h"

void Board::loadMap(std::string path, Snake*& snake)
{
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

	// Update map width/height
	_width = line.length();
	_height = h;

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
