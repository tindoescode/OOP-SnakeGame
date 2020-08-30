#include "MainMenu.h"
#include "Scene.h"
#include "SceneChooseMap.h"

MainMenu::MainMenu(const std::vector<std::string> items, SceneChooseMap& scene) : Menu(items), _attachedScene(scene) {}

void MainMenu::OnItemSelected(int listitem)
{
	//switch (listitem) {
	//case 0: {
	//	_attachedScene.SwitchTo();
	//	break;
	//}
	//case 1: {

	//}
	//case 2: {

	//}
	//}

	_attachedScene.SwitchTo(listitem);

	gotoXY(0, 0);
	TextColor(ColorCode_Yellow);
	std::cout << "Select item " << listitem << std::endl;
}

