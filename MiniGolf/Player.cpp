#include "Player.h"
#include "Util.h"

Player::Player(const int &newid) : id(newid), score(20),
	turns(0), power(0.0), maxPower(0.03), powerUpRate(60) {
}


Player::~Player() {
}

int Player::getScore() {
	return score;
}

void Player::resetScore() {
	score = 20;
}

float Player::getPower() {
	return power;
}

float Player::getMaxPower() {
	return maxPower;
}

// amount of power to charge before striking
void Player::charge() {
	if (power < maxPower) {
		power += (maxPower / powerUpRate);
		if (power > maxPower) {
			power = maxPower;
		}
	}
	//timer(1);
}

void Player::strike(Ball* b) {
	b->push(power);
	power = 0.0;
	score--;
	turns++;
}