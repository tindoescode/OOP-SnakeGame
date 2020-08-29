#pragma once
#include "Console.h"
#include "Menu.h"

class SceneChooseMap;

class MainMenu : public Menu {
private:
	SceneChooseMap& _attachedScene;
public:
	MainMenu(const std::vector<std::string> items, SceneChooseMap& scene);
	void OnItemSelected(int listitem) override;

	//virtual int choose() = 0;
};