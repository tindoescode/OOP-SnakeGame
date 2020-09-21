#include "SceneGame.h"
#include "ScenePause.h"

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
	TextColor(ColorCode_Cyan);

	int x, y;
	//it will be changed when we have more information 
	//draw line at the top of program
	x = 0, y = 0;

	while (x <= _width) {
		gotoXY(_position.X + x, _position.Y + y - 1);
		std::cout << char(205);
		x++;
	}

	//draw line at the bottom of program
	x = 0, y = _height;
	while (x <= _width) {
		gotoXY(_position.X + x, _position.Y + y + 1);
		std::cout << char(205);
		x++;
	}

	//draw line at the left of program
	x = 0, y = 0;
	while (y <= _height) {
		gotoXY(_position.X + x - 1, _position.Y + y);
		std::cout << char(186);
		y++;
	}

	//draw line at the right of program
	x = _width, y = 0;
	while (y <= _height) {
		gotoXY(_position.X + x + 1, _position.Y + y);
		std::cout << char(186);
		y++;
	}

	// top left
	gotoXY(_position.X - 1, _position.Y - 1);
	std::cout << char(201);

	// top right
	gotoXY(_position.X + _width + 1, _position.Y - 1);
	std::cout << char(187);

	// bottom left
	gotoXY(_position.X - 1, _position.Y + _height + 1);
	std::cout << char(200);

	// bottom right
	gotoXY(_position.X + _width + 1, _position.Y + _height + 1);
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
	int maxWidth = 0;

	while (std::getline(f, line))
	{
		if (maxWidth < line.length()) maxWidth = unsigned int (line.length());
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == 'i') // wall
			{
				addObject(ObjectType::wall, _position.X + i, _position.Y + height);
			}
			else if (line[i] == '>') // start
			{
				_snakes.push_back(std::dynamic_pointer_cast<Snake>(addObject(ObjectType::snake, _position.X + i, _position.Y + height)));
			}
			else if (line[i] == 'G') //gate
			{
				_gate = std::dynamic_pointer_cast<Gate>(addObject(ObjectType::gate, _position.X + i, _position.Y + height));
			}
		}
		height++;
	}

	// set width, height
	_width = maxWidth;
	_height = height - 1;

	try {
		if (!_snakes.size()) throw NoSnakeException();
	}
	catch (std::exception& ex) {
		system("cls");
		std::cout << ex.what();
	}

	f.close();
}

void SceneGame::loadSnakeKeyHandle()
{
	_snakes[0]->setSkillKeyHandle([this]() {
		//TODO: the same thing to snake 1
		if (GetAsyncKeyState((int)Key::N1)) {
			TextColor(ColorCode_DarkCyan);
			gotoXY(0, 0);
			std::cout << "Key 1 pressed.";

			if (_snakes[0]->activeItem(1)) {
				TextColor(ColorCode_DarkCyan);
				gotoXY(0, 0);
				std::cout << "Item on slot 1 activated.";
			}
			else {
				TextColor(ColorCode_DarkCyan);
				gotoXY(0, 0);
				std::cout << "You don't have any item on slot 1.";
			}
		}
		else if (GetAsyncKeyState((int)Key::N2)) {
			TextColor(ColorCode_DarkCyan);
			gotoXY(0, 0);
			std::cout << "Key 2 pressed.";

			if (_snakes[0]->activeItem(2)) {
				TextColor(ColorCode_DarkCyan);
				gotoXY(0, 0);
				std::cout << "Item on slot 2 activated.";
			}
			else {
				TextColor(ColorCode_DarkCyan);
				gotoXY(0, 0);
				std::cout << "You don't have any item on slot 2.";
			}
		}
		else if (GetAsyncKeyState((int)Key::N3)) {
			TextColor(ColorCode_DarkCyan);
			gotoXY(0, 0);
			std::cout << "Key L pressed.";

			if (_snakes[0]->activeItem(3)) {
				TextColor(ColorCode_DarkCyan);
				gotoXY(0, 0);
				std::cout << "Item on slot 3 activated.";
			}
			else {
				TextColor(ColorCode_DarkCyan);
				gotoXY(0, 0);
				std::cout << "You don't have any item on slot 3.";
			}
		}
	});

	if (_snakes.size() >= 2) {
		_snakes[1]->setSkillKeyHandle([this]() {
			if (GetAsyncKeyState((int)Key::J)) {
				TextColor(ColorCode_DarkCyan);
				gotoXY(0, 0);
				std::cout << "Key J pressed.";

				if (_snakes[1]->activeItem(1)) {
					TextColor(ColorCode_DarkCyan);
					gotoXY(0, 0);
					std::cout << "Item on slot 1 activated.";
				}
				else {
					TextColor(ColorCode_DarkCyan);
					gotoXY(0, 0);
					std::cout << "You don't have any item on slot 1.";
				}
			}
			else if (GetAsyncKeyState((int)Key::K)) {
				TextColor(ColorCode_DarkCyan);
				gotoXY(0, 0);
				std::cout << "Key K pressed.";

				if (_snakes[1]->activeItem(2)) {
					TextColor(ColorCode_DarkCyan);
					gotoXY(0, 0);
					std::cout << "Item on slot 2 activated.";
				}
				else {
					TextColor(ColorCode_DarkCyan);
					gotoXY(0, 0);
					std::cout << "You don't have any item on slot 2.";
				}
			}
			else if (GetAsyncKeyState((int)Key::L)) {
				TextColor(ColorCode_DarkCyan);
				gotoXY(0, 0);
				std::cout << "Key L pressed.";

				if (_snakes[1]->activeItem(3)) {
					TextColor(ColorCode_DarkCyan);
					gotoXY(0, 0);
					std::cout << "Item on slot 3 activated.";
				}
				else {
					TextColor(ColorCode_DarkCyan);
					gotoXY(0, 0);
					std::cout << "You don't have any item on slot 3.";
				}
			}
		});
	}
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

SceneGame::SceneGame(const int playerNumber, const std::vector<std::string> &maps, SceneStateMachine& sceneStateMachine) : Scene(), _maps(maps), _width(100), _height(30), _fruit(nullptr), _sceneStateMachine(sceneStateMachine),
_pauseScene(0), _position({ 10, 5 }), _currentRound(1), _gate(nullptr), _giftCount(0), _playerNumber(playerNumber)
{
	freeBlock.reset();	
	_lastRound = (unsigned int)maps.size();
}

void SceneGame::OnCreate()
{
	_snakes.clear();
	objects.clear();
	freeBlock.reset();

	_mapPath = _maps[_currentRound - 1];

	// Load map (wall, snake)
	loadMap();

	// Add the second snake
	if (_playerNumber >= 2) {
		auto [X, Y] = getFreeBlock();
		_snakes.push_back(std::dynamic_pointer_cast<Snake>(addObject(ObjectType::snake, X, Y)));
	}

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
	TextColor(ColorCode_DarkYellow);
	gotoXY(5, 0);
	std::cout << "Round " << _currentRound << ", Destination: " << _currentRound * 100 << " points to next round";

	drawSkillBox();
	drawBorder();

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
	if (GetAsyncKeyState(0x57)) { // W
		direction = Direction::up;
		snakeId = 0;
	}
	else if (GetAsyncKeyState(0x53)) { // S
		direction = Direction::down;
		snakeId = 0;
	}
	else if (GetAsyncKeyState(0x41)) { // A
		direction = Direction::left;
		snakeId = 0;
	}
	else if (GetAsyncKeyState(0x44)) { // D
		direction = Direction::right;
		snakeId = 0;
	}

	// Snake 1
	if (GetAsyncKeyState(VK_UP)) { // UP arrow
		direction = Direction::up;
		snakeId = 1;
	}
	else if (GetAsyncKeyState(VK_DOWN)) { // DOWN arrow
		direction = Direction::down;
		snakeId = 1;
	}
	else if (GetAsyncKeyState(VK_LEFT)) { // LEFT arrow
		direction = Direction::left;
		snakeId = 1;
	}
	else if (GetAsyncKeyState(VK_RIGHT)) { // RIGHT arrow
		direction = Direction::right;
		snakeId = 1;
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
	const unsigned int score = _sceneStateMachine.player->getCurrentScore();

	int X, Y;

	for (auto snake : _snakes) {
		X = snake->getX();
		Y = snake->getY();

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
	//show current score
	_sceneStateMachine.player->showCurrentScore();

	for (auto snake : _snakes) {
		std::shared_ptr<Fruit> destinateFruit = nullptr;
		std::shared_ptr<Gift> destinateGift;

		const bool occupied = isOccupied(snake->getX(), snake->getY());
		const unsigned int score = _sceneStateMachine.player->getCurrentScore();

		// Handle collision
		if (occupied) {
			// Things can cause snake to dead
			if (snake->bodyCollision() || snake->wallCollision() || snake->gateCollision(score) == GateCollisionType::border) {
				// If it can go through wall, move more step
				snake->setDead();

				//get current score to calculate total score and reset current score = 0 if snake die
				_sceneStateMachine.player->saveScore();
				_sceneStateMachine.player->resetScore();
			}

			// Fruit/Gift
			else if (destinateFruit = snake->fruitCollision()) {
				// Remove that fruit and plus one more snake segment
				snake->eatFruit(destinateFruit);

				//plus 10 score if snake eat fruit
				if (snake->isX2Point()) {
					_sceneStateMachine.player->addScore(20);
				}
				else {
					_sceneStateMachine.player->addScore(10);
				}

				// Generate a new fruit or a gate when it gets enough points
				if (_sceneStateMachine.player->getCurrentScore() >= _currentRound * 100) {
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
				if (snake->getItem(destinateGift)) {
					gotoXY(0, 0);
					TextColor(ColorCode_Cyan);
					std::cout << "Got a gift";
				}
				else {
					gotoXY(0, 0);
					TextColor(ColorCode_Cyan);
					std::cout << "You don't have any free slot to get gift.";
				}

				_giftCount--;
			}
			else if (snake->gateCollision(score) == GateCollisionType::door) {
				// Get to next round
				_currentRound++;

				if (_currentRound > _lastRound) {
					gotoXY(0, 0);
					std::cout << "Chuc mung, ve nuoc.";

					Sleep(30000);
					// Luu vao bang xep hang cac kieu

					exit(0);
				}
				else {
					// Going to next round, remains snake size
					clrscr();
					OnCreate();
					OnActivate();

					const int plusSize = _sceneStateMachine.player->getCurrentScore() / 10;
					snake->enlonger(plusSize);
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
			OnCreate();
			SwitchTo("SceneGameOver"); // o day no can Id, de t xem lam sao kiem Id cho no
		}

		//1% each 150ms spawn gift
		if (rand() % 100 < 50 && _giftCount <= 2) { //MAX 2 gift at a time
			auto [X, Y] = getFreeBlock();

			std::shared_ptr<Gift> gift = std::dynamic_pointer_cast<Gift>(addObject(ObjectType::gift, X, Y));

			gift->paint();

			_giftCount++;
		}
	}

	// Time delay for the next move
	Sleep(125);
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

void SceneGame::drawSkillBox() {
	drawRect({ 90, 10 }, { 100, 12 });
	drawRect({ 90, 13 }, { 100, 15 });
	drawRect({ 90, 16 }, { 100, 18 });

	TextColor(ColorCode_Pink);

	// Skill1
	gotoXY(88, 11);
	std::cout << "J:";

	gotoXY(91, 11);
	std::cout << "Empty";

	// Skill2
	gotoXY(88, 14);
	std::cout << "K:";

	gotoXY(91, 14);
	std::cout << "Empty";

	// Skill3
	gotoXY(88, 17);
	std::cout << "K:";

	gotoXY(91, 17);
	std::cout << "Empty";
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
