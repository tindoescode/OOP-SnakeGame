#include"PlayerScore.h"

PlayerScore::PlayerScore() {
	for (int i = 0; i < 4; i++) {
		currentScore[i] = 0;
		totalScore[i] = 0;
	}
}
void PlayerScore::setScoreForNewGame(int i) {
	if (i >= 4)	return;
	currentScore[i] = 0;
}
void PlayerScore::addScore(int i) {
	currentScore[i]++;
	totalScore[i]++;
}
int PlayerScore::getCurrentScore(int i) {
	return currentScore[i];
}
int PlayerScore::getTotalScore(int i) {
	return totalScore[i];
}

void PlayerScore::sumScore(int i) {
	totalScore[i] += currentScore[i];
}

void PlayerScore::showCurrentScore(int i) {
	gotoXY(103, 3);
	std::cout << "Total Scoce: " << totalScore[i];
	gotoXY(103, 4);
	std::cout << "Your Score: " << currentScore[i];
}