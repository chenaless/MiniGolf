#include "MenuScreen.h"

#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>

MenuScreen::MenuScreen() : playerInfo(NULL) {
}

MenuScreen::MenuScreen(Player* pl) {
	playerInfo = pl;
}

MenuScreen::~MenuScreen() {
	playerInfo = NULL;
}

void MenuScreen::draw(const int &lev) { // tmp
    glDisable( GL_LIGHTING );

    glLoadIdentity();

	orthoBegin();
		glColor3f(1.0f, 1.0f, 1.0f);
		
		drawLevelSelection(lev);

    orthoEnd();

    glEnable( GL_LIGHTING );
}

void MenuScreen::setPlayerProfile(Player* p) {
}

// to move input handler of menu selection here
int MenuScreen::drawLevelSelection(const int &lvl) { // currlvl = ...
	this->drawString(10, 12, "Select a Level:");
	this->drawString(10, 20, pickLevel(lvl).c_str());
	this->drawString(10, 36, "'m' for up");
	this->drawString(10, 44, "'n' for down");
	this->drawString(10, 52, "'x' to select");

	return lvl;
}

void MenuScreen::showTopScore() {
}

string MenuScreen::pickLevel(const int &id) {
	stringstream stats;
	stats << "LEVEL: " << (id+1);
	return stats.str();
}