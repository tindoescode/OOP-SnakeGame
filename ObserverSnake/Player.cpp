#include"Player.h"

Player::Player() {
	for (int i = 0; i < 4; i++) {
		currentScore[i] = 0;
		totalScore[i] = 0;
	}
}
void Player::resetScore(int i) {
	if (i >= 4)	return;
	currentScore[i] = 0;
}
void Player::addScore(int i) {
	currentScore[i]++;
	totalScore[i]++;
}
int Player::getCurrentScore(int i) {
	return currentScore[i];
}
int Player::getTotalScore(int i) {
	return totalScore[i];
}

void Player::saveScore(int i) {
	totalScore[i] += currentScore[i];
}

void Player::showCurrentScore(int i) {
	gotoXY(103, 3);
	std::cout << "Total Scoce: " << totalScore[i];
	gotoXY(103, 4);
	std::cout << "Your Score: " << currentScore[i];
}