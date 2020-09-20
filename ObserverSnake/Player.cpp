#include"Player.h"

Player::Player() {
	currentScore = 0;
	totalScore = 0;
}
void Player::resetScore() {
	currentScore = 0;
}
void Player::addScore(int score) {
	currentScore += score;
	totalScore += score;
}
unsigned int Player::getCurrentScore() {
	return currentScore;
}
unsigned int Player::getTotalScore() {
	return totalScore;
}

void Player::saveScore() {
	totalScore += currentScore;
}

void Player::showCurrentScore() {
	gotoXY(103, 3);
	std::wcout << "Total Score: " << totalScore;
	gotoXY(103, 4);
	std::wcout << "Your Score: " << currentScore;
}