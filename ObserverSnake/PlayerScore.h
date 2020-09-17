#pragma once
#include <iostream>
#include"Console.h"
class PlayerScore {
private:
	int currentScore[4];	//arr use to save current score of 4 maps
	int totalScore[4];		//arr use to save total score of each map
public:

	PlayerScore();
	void setScoreForNewGame(int i);
	void addScore(int i);
	int getCurrentScore(int i);
	int getTotalScore(int i);
	void sumScore(int i);
	void showCurrentScore(int i);
};

