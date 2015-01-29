#pragma once
#include <GL/glew.h>
#include <GL/glut.h>

#include "Ball.h"

class Player {
public:
	Player(const int &);
	~Player();
	string name;
	int id;
	int getScore();
	void resetScore(); // for each new starting level
	float getPower();
	float getMaxPower();
	void charge();
	void strike(Ball*);
private:
	int score;
	int turns;
	float power;
	float maxPower;
	float powerUpRate; // greater, the slower
};

