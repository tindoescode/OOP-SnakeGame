#include "SceneGame.h"
#include "ScenePause.h"

Object* SceneGame::addObject(ObjectType type, int x, int y) {
	Object* object;

	if (type == ObjectType::snake) {
		object = new Snake(x, y, this); // pass scene game so snake can interact with scene game's objects
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
	
	setOccupiedBlock(x, y);

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
		std::cout << char(205);
		x++;
	}

	//draw line at the bottom of program
	x = 0, y = 30;
	while (x <= _width) {
		gotoXY(x, y);
		std::cout << char(205);
		x++;
	}

	//draw line at the left of program
	x = 0, y = 0;
	while (y <= _height) {
		gotoXY(x, y);
		std::cout << char(186);
		y++;
	}

	//draw line at the right of program
	x = 100, y = 0;
	while (y <= _height) {
		gotoXY(x, y);
		std::cout << char(186);
		y++;
	}

	// top left
	gotoXY(0, 0);
	std::cout << char(201);

	// top right
	gotoXY(_width, 0);
	std::cout << char(187);

	// bottom left
	gotoXY(0, _height);
	std::cout << char(200);

	// bottom right
	gotoXY(_width, _height);
	std::cout << char(188);

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
		for (int i = 0; i < line.length(); i++)
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
	return freeBlock[y * MAX_X + x];
}

void SceneGame::deleteSnakeSegment(int x, int y) {
	for (auto i = objects.begin(); i != objects.end(); i++) {
		if ((*i)->getX() == x && (*i)->getY() == y && dynamic_cast<SnakeSegment*>(*i)) {
			delete* i;
			objects.erase(i);
			setOccupiedBlock(x, y, 0);
			break;
		}
	}
}

void SceneGame::deleteFruit(int x, int y) {
	for (auto i = objects.begin(); i != objects.end(); i++) {
		if ((*i)->getX() == x && (*i)->getY() == y && dynamic_cast<Fruit*>(*i)) {
			delete* i;
			objects.erase(i);			
			setOccupiedBlock(x, y, 0);
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

void SceneGame::setOccupiedBlock(int x, int y, unsigned int occupied)
{
	// see that Y is row, and X is column in console.
	auto index = y * MAX_X + x; // stand for bitmap index

	if (index < 0 || index >= MAX_X * MAX_Y) return;
	
 	freeBlock.set(y * MAX_X + x, occupied);
}

SceneGame::SceneGame(std::string mapPath, SceneStateMachine& sceneStateMachine)
	: Scene(), _mapPath(mapPath), _width(100), _height(30), _snake(nullptr), _fruit(nullptr), _sceneStateMachine(sceneStateMachine),
	_pauseScene(0)
{
	Nocursortype();
}

void SceneGame::OnCreate()
{
	objects.clear();
	freeBlock.reset();

	// Load map (wall, snake)
	loadMap(_mapPath, _snake);
	// Create fruit
	auto [X, Y] = getFreeBlock();
	_fruit = dynamic_cast<Fruit*>(addObject(ObjectType::fruit, X, Y));
}

void SceneGame::OnDestroy()
{
}

void SceneGame::OnActivate()
{
	drawBorder();

	for (auto i : objects) {
		i->paint();
	}
}

void SceneGame::OnDeactivate()
{
	system("cls");
}

void SceneGame::ProcessInput()
{
	//Handle ESC Key
	if (GetAsyncKeyState(VK_ESCAPE)) {
		_pauseScene->SetContinueScene(_sceneStateMachine.GetCurrentScene());
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
	//show current score
	_sceneStateMachine.player->showCurrentScore(_sceneStateMachine.curSceneID);

	Fruit* destinateFruit = nullptr;

	// Handle collision
	if (_snake->bodyCollision()) {
		_snake->setDead();

		//get current score to calculate total score and reset current score = 0 if snake die
		_sceneStateMachine.player->saveScore(_sceneStateMachine.curSceneID);
		_sceneStateMachine.player->resetScore(_sceneStateMachine.curSceneID);
	}
	else if (_snake->wallCollision()) {
		_snake->setDead();

		//get current score to calculate total score and reset current score = 0 if snake die
		_sceneStateMachine.player->saveScore(_sceneStateMachine.curSceneID);
		_sceneStateMachine.player->resetScore(_sceneStateMachine.curSceneID);
	}
	else if (destinateFruit = _snake->matchFruit()) {
		_snake->eatFruit(destinateFruit);
		_fruit = dynamic_cast<Fruit*>(objects[objects.size()-1]);

		//plus 1 score if snake eat fruit
		_sceneStateMachine.player->addScore(_sceneStateMachine.curSceneID);
	}

	_snake->paint();

	// Time for the next move
	Sleep(100);

	if (_snake->isdead()) {
		OnCreate();
		OnActivate();
		SwitchTo("SceneGameOver"); // o day no can Id, de t xem lam sao kiem Id cho no
	}
}

COORD SceneGame::getFreeBlock() {
	short X, Y;
	do {
		X = 1 + rand() % (_width - 1);
		Y = 1 + rand() % (_height - 1);
	} while (freeBlock[X * MAX_X + Y] == 1);

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

