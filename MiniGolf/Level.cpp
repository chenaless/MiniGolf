#include "Level.h"
#include "Tee.h"
#include "Cup.h"

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <GL/glew.h>
#include <GL/glut.h>

using namespace std;

Level::Level() : physics(new Physics()), ball(NULL), hiScore(0), won(false) {
}

Level::~Level() {
	// clean up objlist
	if (!objlist.empty()) {
		list<GameObject*>::iterator old = objlist.begin();
		list<GameObject*>::iterator end = objlist.end();
		for (; old != end; ++old) {
			if (*old) {
				delete (*old);
				(*old) = NULL;
			}
		}
	}
	objlist.clear();
	
	// clan up tilemap
	if (!tilemap.empty()) {
		map<int, Tile*>::iterator old_m = tilemap.begin();
		map<int, Tile*>::iterator end_m = tilemap.end();
		for (; old_m != end_m; ++old_m) {
			if ((*old_m).second) { // delete tiles
				delete ((*old_m).second);
				((*old_m).second) = NULL;
			}
		}
	}

	if (physics != NULL)
		delete physics;
	physics = NULL;
}

void Level::load(const string &filename) {
	won = false; // loading a new level

	cout << filename << endl;
	ifstream fin;

	// open input file (load level)
	fin.open(filename);
	if (!fin) {
		cerr << "Unable to open file" << endl;
		exit(-1);
	}

	// file data extraction
	char line[256];

	while (!fin.eof()) {
		fin.getline(line, 256);
		char *data = strtok(line," ");
		if (data != NULL) {

			if (strcmp(data, "tile") == 0) {
				data = strtok (NULL, " ");
				int id = atoi(data); // get id num
				tilemap[id] = new Tile(data);
			} else if (strcmp(data, "tee") == 0) {
				Tee *tee = new Tee(data);
				objlist.push_back(tee);
				ball = new Ball(tee->getCoord(), tee->getTileID());
			} else if (strcmp(data, "cup") == 0) {
				cup = new Cup(data);
				objlist.push_back(cup);
			}

		}
	}

	fin.close();
}

void Level::update() {
	// put player/ball interaction logic here
		if (ball->tileID == cup->getTileId()) {
			//cout << "ball-tee" << endl;
			if (physics->collision(ball->pos, cup->pos, ball->getRadius(), cup->getRadius())) {
				if (ball->vel <= 0.003f) {// min vel not to pass over hole
				won = true;
				cout << "Winner!" << endl;
				// end game
				// save score (based on # turns)
				// load new level
				}
			}
		}
		physics->applyBallPhysics(ball, tilemap[ball->tileID]);
}

void Level::draw() {
	// draw tiles
		map<int, Tile*>::iterator ti = tilemap.begin();
		map<int, Tile*>::const_iterator ti_end = tilemap.end();
		for (; ti != ti_end; ++ti) {
			if ((*ti).second) {
				(*ti).second->draw();
				(*ti).second->drawEdges();
			}
		}

		// draw game objects
		list<GameObject*>::iterator obj = objlist.begin();
		list<GameObject*>::const_iterator obj_end = objlist.end();
		for (; obj != obj_end; ++obj) {
			(*obj)->draw();
		}

		// draw ball
		ball->draw();
		ball->drawDirection();
}

void Level::setHiScore(Player* p) {
	if (p->getScore() > hiScore)
		hiScore = p->getScore();
}

bool Level::wonGame() {
	return won;
}

Ball* Level::getBall() {
	return ball;
}