#pragma once
#include <list>
#include <map>
#include <string>

#include "Physics.h"
#include "Player.h"
#include "Ball.h"
#include "Cup.h"
#include "Tee.h"
#include "Tile.h"
#include "GameObject.h"
#include "Shader.h"

class Level {
public:
	Level();
	~Level();
	void load(const string &);
	void update();
	void draw();
	void setHiScore(Player*);
	bool wonGame();
	Ball* getBall();
private:
	map<int, Tile*> tilemap;
	list<GameObject*> objlist;
	Physics* physics;
	Ball *ball;
	Cup *cup;
	int hiScore;
	bool won;
};
