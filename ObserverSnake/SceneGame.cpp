#include "SceneGame.h"
#include "ScenePause.h"
#include "Game.h"
#include <sstream>
#include <limits>

SceneGame::SceneGame(const unsigned int playerNumber, const std::vector<std::wstring>& maps, SceneStateMachine& sceneStateMachine) : Scene(), _maps(maps), _width(100), _height(30), _fruit(nullptr), _sceneStateMachine(sceneStateMachine),
_pauseScene(0), _position({ SCREEN_WIDTH / 6, SCREEN_HEIGHT / 4 + 1}), _currentRound(1), _gate(nullptr), _giftCount(0), _playerNumber(playerNumber)
{
	freeBlock.reset();
	_lastRound = (unsigned int)maps.size();
}

void SceneGame::ShowTopTitle() {
	Console::TextColor(ColorCode_Green);

	std::vector<std::string> title = {
"   .-'''-. ,---.   .--.   ____    .--.   .--.      .-''-.   \n",
"  / _     \\|    \\  |  | .'  __ `. |  | _/  /     .'_ _   \\  \n",
" (`' )/`--'|  ,  \\ |  |/   '  \\  \\| (`' ) /     / ( ` )   ' \n",
"(_ o _).   |  |\\_ \\|  ||___|  /  ||(_ ()_)     . (_ o _)  | \n",
" (_,_). '. |  _( )_\\  |   _.-`   || (_,_)   __ |  (_,_)___| \n",
".---.  \\  :| (_ o _)  |.'   _    ||  |\\ \\  |  |'  \\   .---. \n",
"\\    `-'  ||  (_,_)\\  ||  _( )_  ||  | \\ `'   / \\  `-'    / \n",
" \\       / |  |    |  |\\ (_ o _) /|  |  \\    /   \\       /  \n",
"  `-...-'  '--'    '--' '.(_,_).' `--'   `'-'     `'-..-'   \n",
	};

	auto marginLeft = SCREEN_WIDTH / 2 - title[0].size() / 2;
	int j = 1;
	for (auto i : title) {
		Console::gotoXY(marginLeft, j++);
		std::cout << i;
	}

}

std::shared_ptr<Object> SceneGame::addObject(ObjectType type, int x, int y) {
	std::shared_ptr<Object> object;

	if (type == ObjectType::snake) {
		object = std::make_shared<Snake>(x, y, shared_from_this()); // pass scene game so snake can interact with scene game's objects
	}
	else if (type == ObjectType::snake_segment) {
		object = std::make_shared<SnakeSegment>(x, y);
	}
	else if (type == ObjectType::fruit) {
		object = std::make_shared<Fruit>(x, y);
	}
	else if (type == ObjectType::wall) {
		object = std::make_shared<Wall>(x, y);
	}
	else if (type == ObjectType::gate) {
		object = std::make_shared<Gate>(x, y);
	}
	else if (type == ObjectType::gift) {
		object = std::make_shared<Gift>(x, y);
	}
	objects.push_back(object);
	
	// Set coordinate occupied
	for (int i = 0; i < object->getWidth(); i++) {
		for (int j = 0; j < object->getHeight(); j++) {
			setOccupiedBlock(x + i, y + j);
		}
	}

	return object;
}

void SceneGame::drawBorder() {
	Console::TextColor(ColorCode_DarkYellow);

	int x, y;
	//it will be changed when we have more information 
	//draw line at the top of program
	x = 0, y = 0;

	while (x <= _width) {
		Console::gotoXY(_position.X + x, _position.Y + y - 1);
		std::cout << char(205);
		x++;
	}

	//draw line at the bottom of program
	x = 0, y = _height;
	while (x <= _width) {
		Console::gotoXY(_position.X + x, _position.Y + y + 1);
		std::cout << char(205);
		x++;
	}

	//draw line at the left of program
	x = 0, y = 0;
	while (y <= _height) {
		Console::gotoXY(_position.X + x - 1, _position.Y + y);
		std::cout << char(186);
		y++;
	}

	//draw line at the right of program
	x = _width, y = 0;
	while (y <= _height) {
		Console::gotoXY(_position.X + x + 1, _position.Y + y);
		std::cout << char(186);
		y++;
	}

	// top left
	Console::gotoXY(_position.X - 1, _position.Y - 1);
	std::cout << char(201);

	// top right
	Console::gotoXY(_position.X + _width + 1, _position.Y - 1);
	std::cout << char(187);

	// bottom left
	Console::gotoXY(_position.X - 1, _position.Y + _height + 1);
	std::cout << char(200);

	// bottom right
	Console::gotoXY(_position.X + _width + 1, _position.Y + _height + 1);
	std::cout << char(188);

}

void SceneGame::loadMap() {
	std::ifstream f;

	f.open(_mapPath, std::ios::in);

	//TODO: make it library
	try {
		if (!f.is_open()) throw FileNotFoundException();
	}
	catch (std::exception& ex) {
		system("cls");
		std::cout << ex.what();
	}

	std::string line;
	int height = 0;

	// we want our map be center
	f >> _width;
	
	// Skip \n
	f.seekg(2, std::ios::cur);

	_position.X = SCREEN_WIDTH / 2 - _width / 2;

	while (std::getline(f, line))
	{
		for (int i = 0, j = line.size(); i < j; i++)
		{
			if (line[i] == 'i') // wall
			{
				addObject(ObjectType::wall, _position.X + i, _position.Y + height);
			}
			else if (line[i] == '>') // start
			{
				if(!_snakes.size()) _snakes.push_back(std::dynamic_pointer_cast<Snake>(addObject(ObjectType::snake, _position.X + i, _position.Y + height)));
				else {
					_snakes[0]->setPos(_position.X + i, _position.Y + height);
				}
			}
			else if (line[i] == 'G') //gate
			{
				_gate = std::dynamic_pointer_cast<Gate>(addObject(ObjectType::gate, _position.X + i, _position.Y + height));
			}
		}
		height++;
	}

	// set width, height
	_height = height - 1;
	
	try {
		if (!_snakes.size()) throw NoSnakeException();
	}
	catch (std::exception& ex) {
		system("cls");
		std::cout << ex.what();
	}

	// Add the second snake
	if (_playerNumber >= 2) {
		auto [X, Y] = getFreeBlock();
		auto snake = std::dynamic_pointer_cast<Snake>(addObject(ObjectType::snake, X, Y));
		snake->setColor(ColorCode_Pink);
		snake->setCharacter(char(238));

		// Bind player indx 1 if there are two players

		_snakes.push_back(snake);
	}

	f.close();
}

void SceneGame::loadSnakeKeyHandle()
{
	if (_snakes.size() > 0)
		_snakes[0]->setSkillKey({ {'1', Key::N1}, {'2', Key::N2}, {'3', Key::N3} });
	
	if(_snakes.size() > 1)
		_snakes[1]->setSkillKey({ {'J', Key::J},  {'K', Key::K},  {'L', Key::L}  });
}

bool SceneGame::isOccupied(int x, int y) {
	return freeBlock.test(y * MAX_X + x);
}

void SceneGame::deleteSnakeSegment(int x, int y) {
	for (auto i = objects.begin(); i != objects.end(); i++) {
		if ((*i)->getX() == x && (*i)->getY() == y && std::dynamic_pointer_cast<SnakeSegment>(*i)) {
			objects.erase(i);
			setOccupiedBlock(x, y, 0);
			break;
		}
	}
}

void SceneGame::deleteFruit(int x, int y) {
	for (auto i = objects.begin(); i != objects.end(); i++) {
		if ((*i)->getX() == x && (*i)->getY() == y && std::dynamic_pointer_cast<Fruit>(*i)) {
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

void SceneGame::initializeSavedData(COORD fruit, COORD snakeHead, std::vector<COORD> snakeSegments, unsigned int round, Direction dir) {
	// A semi OnCreate for loading game
	objects.clear();
	freeBlock.reset();

	_playerNumber = 1;
	_currentRound = round;
	_mapPath = _maps[_currentRound - 1];
	
	// I just want to load the map, not snake or create random fruit
	loadMap();

	// Atempt to clear old moveable/fruit object
	_snakes.clear();
	deleteFruit(getFruit()->getX(), getFruit()->getY());

	// Assign new
	_fruit = std::dynamic_pointer_cast<Fruit>(addObject(ObjectType::fruit, fruit.X, fruit.Y));
	_snakes.push_back(std::dynamic_pointer_cast<Snake>(addObject(ObjectType::snake, snakeHead.X, snakeHead.Y)));
	
	_snakes[0]->setDirection(dir);
	_snakes[0]->enlonger(snakeSegments.size());
	_snakes[0]->bindPlayer(_sceneStateMachine.getPlayer(0));

	loadSnakeKeyHandle();
}

void SceneGame::OnCreate()
{
	for (auto snake : _snakes) {
		snake->resetStatus();
	}

	objects.clear();
	freeBlock.reset();
	_giftCount = 0;
	_mapPath = _maps[_currentRound - 1];

	// Load map (wall, snake)
	loadMap();

	// Bind player to make use of UI
	if(_snakes.size() >= 1) _snakes[0]->bindPlayer(_sceneStateMachine.getPlayer(0));
	if(_snakes.size() >= 2) _snakes[1]->bindPlayer(_sceneStateMachine.getPlayer(1));

	// Initialize controller for each snake
	loadSnakeKeyHandle();

	// Create fruit
	COORD block = getFreeBlock();
	_fruit = std::dynamic_pointer_cast<Fruit>(addObject(ObjectType::fruit, block.X, block.Y));
}

void SceneGame::OnDestroy()
{
}

void SceneGame::OnActivate()
{
	// UI
	ShowTopTitle();
	drawBorder();
	drawSkillBox(); // for each snake

	// Draw mission
	Console::TextColor(ColorCode_DarkYellow);
	Console::gotoXY(5, 0);
	std::cout << "Round " << _currentRound << ", Destination: " << _currentRound * 100 << " points to next round";

	// Draw all objects except gate
	for (auto i : objects) {
		if(!std::dynamic_pointer_cast<Gate>(i)) i->paint();
	}
}

void SceneGame::OnDeactivate()
{
	system("cls");
}

void SceneGame::ProcessInput()
{
	fflush(stdin);

	//Handle ESC Key
	if (GetAsyncKeyState(VK_ESCAPE)) {
		_pauseScene->SetContinueScene(_sceneStateMachine.GetCurrentScene());
		SwitchTo("PauseScene");
	}
	
	for(auto snake : _snakes) {
		snake->HandleSkillKey();
	}

	// Game loop
	Direction direction = Direction::idle;
	int snakeId = -1;

	// Snake 0
	if (_kbhit()) {
		switch (Key(_getch())) {
		case Key::W:
			direction = Direction::up;
			snakeId = 0;
			break;
		case Key::S:
			direction = Direction::down;
			snakeId = 0;
			break;
		case Key::A:
			direction = Direction::left;
			snakeId = 0;
			break;
		case Key::D:
			direction = Direction::right;
			snakeId = 0;
			break;
		case Key(224):
			switch (Key(_getch())) {
			case Key::VKUP:
				direction = Direction::up;
				snakeId = 1;
				break;
			case Key::VKDOWN:
				direction = Direction::down;
				snakeId = 1;
				break;
			case Key::VKLEFT:
				direction = Direction::left;
				snakeId = 1;
				break;
			case Key::VKRIGHT:
				direction = Direction::right;
				snakeId = 1;
				break;
			}
		}
	}


	if (_playerNumber < 2) {
		snakeId = 0;
	}

	if (snakeId != -1)
	{
		_snakes[snakeId]->turnHead(direction);
	}
}

void SceneGame::Update()
{
	// calculate next step, checking if snake could get die -> move next step
	int step = 1;
	
	for (auto snake : _snakes) {
		const unsigned int score = snake->getPlayer()->getCurrentScore();
		
		const int X = snake->getX();
		const int Y = snake->getY();

		while (
			isOccupied(X, Y)
			&& snake->isThroughWall()
			&& snake->dieInNextStep(step, score)) {
			step++;
		}

		snake->move(step);
	}
}

void SceneGame::LateUpdate()
{
	for (auto snake : _snakes) {
		std::shared_ptr<Fruit> destinateFruit = nullptr;
		std::shared_ptr<Gift> destinateGift;

		const bool occupied = isOccupied(snake->getX(), snake->getY());
		const unsigned int score = snake->getPlayer()->getCurrentScore();

		// Handle collision
		if (occupied && !snake->isStandingStill()) {
			// Things can cause snake to dead
			if (snake->bodyCollision() || snake->wallCollision() || snake->gateCollision(score) == GateCollisionType::border) {
				// If it can go through wall, move more step
				snake->setDead();

				//get current score to calculate total score and reset current score = 0 if snake die
				snake->getPlayer()->saveScore();
				snake->getPlayer()->resetScore();

				saveScore();
			}

			// Fruit/Gift
			else if (destinateFruit = snake->fruitCollision()) {
				// Remove that fruit and plus one more snake segment
				snake->eatFruit(destinateFruit);

				//plus 10 score if snake eat fruit
				if (snake->isX2Point()) {
					snake->getPlayer()->addScore(20);
				}
				else {
					snake->getPlayer()->addScore(10);
				}

				// Generate a new fruit or a gate when it gets enough points
				if (snake->getPlayer()->getCurrentScore() >= _currentRound * 100) {
					// Add a gate instead

					_gate->paint();
				}
				else {
					// Add a fruit
					auto [X, Y] = getFreeBlock();

					_fruit = std::dynamic_pointer_cast<Fruit>(addObject(ObjectType::fruit, X, Y));
					_fruit->paint();
				}

			}
			else if (destinateGift = snake->giftCollision()) {
				int i = 0;
				if (!snake->getItem(destinateGift)) {
					Console::gotoXY(0, 0);
					Console::TextColor(ColorCode_Cyan);
					std::cout << "You don't have any free slot to get gift.";
				}

				_giftCount--;
			}
			else if (snake->gateCollision(score) == GateCollisionType::door) {
				// Get to next round
				_currentRound++;

				if (_currentRound > _lastRound) {
					Console::gotoXY(0, 0);
					std::cout << "Congratulations, you won.";

					Sleep(1500);
					// Luu vao bang xep hang cac kieu

					SwitchTo(0);
				}
				else {
					// Going to next round, remains snake size
					Console::clrscr();
					OnCreate();
					OnActivate();

					// Reset snake status like: direction, buff..
					snake->resetStatus();

					// Give it size proper with its points
					//const int plusSize = snake->getPlayer()->getCurrentScore() / 10;
					//snake->enlonger(plusSize);
				}
			}
		}
		snake->paint();

		//
		snake->ThroughWallDecrease();
		snake->SpeedTimeDecrease();
		snake->X2PointDecrease();

		// Check dead
		if (snake->isdead()) {
			_currentRound = 1;
			_snakes.clear();
			OnCreate();
			
			SwitchTo("SceneGameOver"); // o day no can Id, de t xem lam sao kiem Id cho no
		}

		//1% each 150ms spawn gift
		if (rand() % 100 > 98 && _giftCount < 1) { //MAX 2 gift at a time
			auto [X, Y] = getFreeBlock();

			std::shared_ptr<Gift> gift = std::dynamic_pointer_cast<Gift>(addObject(ObjectType::gift, X, Y));

			gift->paint();

			_giftCount++;
		}

		//show current score
		snake->getPlayer()->showCurrentScore();
	}

	// Time delay for the next move
	double max = 1.0;
	for (auto snake : _snakes) {
		if (max < snake->getSpeed()) max = snake->getSpeed();
	}

	Sleep(static_cast<DWORD>((double)125 / max));
}

COORD SceneGame::getFreeBlock() {
	short X, Y;
	do {
		X = _position.X + rand() % (_width);
		Y = _position.Y + rand() % (_height);
	} while (freeBlock.test(MAX_X * Y + X));

	return { X, Y };
}
void SceneGame::Draw()
{
}

void SceneGame::drawSkillBox()
{
	for (auto snake : _snakes) {
		snake->drawSkillBox();
	}
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

void SceneGame::saveScore() {
	// Score board is just for single player
	if (_playerNumber > 1) return;

	//
	std::fstream f("ScoreBoard.txt", std::ios::in || std::ios::out);
	std::string line;

	int countline = 0;

	std::vector<std::string>temp;

	for(int i = 0; i < 10; i++) 
		temp.push_back("");

	int i = 0;
	while (getline(f, line)) {
		temp[i] = line;
	}

	for (int i = 0; i < temp.size(); i++) {
		if (atoi(temp[i].substr(temp[i].rfind(" ") + 1, line.size() - temp[9].rfind(" ") - 1).c_str()) < _snakes.front()->getPlayer()->getTotalScore())
		{
			Console::TextColor(ColorCode_DarkRed);
			Console::gotoXY(15, 15);
			std::cout << "Your score is in top 10 !!! Please enter your name (< 10 characters):";
			Console::gotoXY(15, 16);
			std::cout << "Enter your name (< 10 characters):";

			Console::gotoXY(15, 17);

			getline(std::cin, line);

			std::stringstream input;
			input << i + 1 << "." << line << " " << _lastRound << " " << _snakes.front()->getPlayer()->getTotalScore();
			temp[i] = input.str();
			break;
		}
	}
	f.close();

	f.open("ScoreBoard.txt", std::ios::out);
	for (int i = 0; i < temp.size(); i++) {
		f << temp[i] << std::endl;
	}
	f.close();
}
