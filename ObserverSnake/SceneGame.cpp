#include "SceneGame.h"
#include "ScenePause.h"

Object* SceneGame::addObject(ObjectType type, size_t x, size_t y) {
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

void SceneGame::drawBorder() {
	TextColor(ColorCode_Cyan);

	int x, y;
	//it will be changed when we have more information 
	//draw line at the top of program
	x = 0, y = 0;
	while (x <= _width) {
		gotoXY(x, y);
		std::wcout << 'x';
		x++;
	}

	//draw line at the bottom of program
	x = 0, y = 30;
	while (x <= _width) {
		gotoXY(x, y);
		std::wcout << 'x';
		x++;
	}

	//draw line at the left of program
	x = 0, y = 0;
	while (y <= _height) {
		gotoXY(x, y);
		std::wcout << 'x';
		y++;
	}

	//draw line at the right of program
	x = 100, y = 0;
	while (y <= _height) {
		gotoXY(x, y);
		std::wcout << 'x';
		y++;
	}
}

void SceneGame::loadMap(std::string path, Snake*& snake) {
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

	try {
		if (!snake) throw NoSnakeException();
	}
	catch (std::exception& ex) {
		system("cls");
		std::cout << ex.what();
	}

	f.close();
}

bool SceneGame::isOccupied(int x, int y) {
	for (auto i : objects) {
		if (i->getX() == x && i->getY() == y) return true;
	}
	return false;
}

void SceneGame::deleteSnakeSegment(int x, int y) {
	for (auto i = objects.begin(); i != objects.end(); i++) {
		if ((*i)->getX() == x && (*i)->getY() == y && dynamic_cast<SnakeSegment*>(*i)) {
			delete* i;
			objects.erase(i);
			break;
		}
	}
}

void SceneGame::deleteFruit(int x, int y) {
	for (auto i = objects.begin(); i != objects.end(); i++) {
		if ((*i)->getX() == x && (*i)->getY() == y && dynamic_cast<Fruit*>(*i)) {
			delete* i;
			objects.erase(i);
			break;
		}
	}
}

int SceneGame::getWidth() {
	return _width;
}

int SceneGame::getHeight() {
	return _height;
}

SceneGame::SceneGame(std::string mapPath, SceneStateMachine& sceneStateMachine) 
	: Scene(), _mapPath(mapPath), _width(100), _height(30), _snake(nullptr), _fruit(nullptr), _sceneStateMachine(sceneStateMachine),
	_escScene(0)
{
	Nocursortype();
}

void SceneGame::OnCreate()
{
	// Load map (wall, snake)
	loadMap(_mapPath, _snake);
}

void SceneGame::OnDestroy()
{
}

void SceneGame::OnActivate()
{
	drawBorder();

	// Create fruit
	auto [X, Y] = getFreeBlock();
	_fruit = dynamic_cast<Fruit*>(addObject(ObjectType::fruit, X, Y));

	for (auto i : objects) {
		i->paint();
	}
}

void SceneGame::OnDeactivate()
{
}

void SceneGame::ProcessInput()
{
	//Handle ESC Key
	if (GetAsyncKeyState(VK_ESCAPE)) {
		_escScene->SetContinueScene(_sceneStateMachine.GetCurrentScene());
		SwitchTo("PauseScene");
	}

	// Game loop
	char op;
	
	if (_kbhit())
	{
		// Create a new head segment, delete tail segment
		op = tolower(_getch());

		_snake->turnHead(Direction(op));
	}
}

void SceneGame::Update()
{
	_snake->move();
}

void SceneGame::LateUpdate()
{
	Fruit* destinateFruit = nullptr;

	// Handle collision
	if (_snake->bodyCollision()) {
		_snake->setDead();
	}
	else if (_snake->wallCollision()) {
		_snake->setDead();
	}
	else if (destinateFruit = _snake->matchFruit()) {
		_snake->eatFruit(destinateFruit);
	}

	// if _snake get over border
	if (_snake->getX() > _width) {
		_snake->setPos(0, _snake->getY());
	}
	else if (_snake->getX() < 0) {
		_snake->setPos(_width, _snake->getY());
	}
	else if (_snake->getY() > _height) {
		_snake->setPos(_snake->getX(), 0);
	}
	else if (_snake->getY() < 0) {
		_snake->setPos(_snake->getX(), _height);
	}

	_snake->paint();
	// Time for the next move
	Sleep(100);

	if (_snake->isdead()) {
		SwitchTo("SceneGameOver"); // o day no can Id, de t xem lam sao kiem Id cho no
	}
}

COORD SceneGame::getFreeBlock() {
	short X, Y;
	do {
		X = rand() % _width;
		Y = rand() % _height;
	} while (isOccupied(X, Y));

	return { X, Y };
}
void SceneGame::Draw()
{
}

// Cai nay de de~ dang nhan du lieu scene o Game.cpp
void SceneGame::SetSwitchToScene(std::unordered_map<std::string, unsigned int> stateInf)
{
	// Stores the id of the scene that we will transition to.
	_stateInf.merge(stateInf);
}

void SceneGame::SwitchTo(std::string mapName) // nay nhan vao mapName, la cai chuoi~ string dau tien
{
	auto it = _stateInf.find(mapName);

	if (it != _stateInf.end()) {
		_sceneStateMachine.SwitchTo(it->second);
	}
}