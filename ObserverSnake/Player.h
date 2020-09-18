#pragma once
#include <iostream>
#include"Console.h"
class Player {
private:
	int currentScore[4];	//arr use to save current score of 4 maps
	int totalScore[4];		//arr use to save total score of each map
public:

	Player();
	void resetScore(int i);
	void addScore(int i);
	int getCurrentScore(int i);
	int getTotalScore(int i);
	void saveScore(int i);
	void showCurrentScore(int i);
};

