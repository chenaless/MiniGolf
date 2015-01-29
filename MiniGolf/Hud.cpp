#include "Hud.h"

#include <sstream>
#include <cstring>
#include <GL/glew.h>
#include <GL/glut.h>

Hud::Hud(Player* pinfo, Camera* cstats) : barWidth(25), maxBarHeight(40) {
	playerInfo = pinfo;
	camStats = cstats;
}


Hud::~Hud()
{
	// no need to delete pointed objects; they will clean themselves
}

void Hud::draw() {
	orthoBegin();
		glColor3f(1.0f, 1.0f, 1.0f);
		
		this->drawString(10, 12, showCameraStats().c_str());
		this->drawString(10, 20, showPlayerInfo().c_str());

		drawPowerBar();

    orthoEnd();
}

// to display scores at end of game
void Hud::drawResults() {
	orthoBegin();
		glColor3f(1.0f, 1.0f, 1.0f);
		
		this->drawString(10, 12, "LEVEL COMPLETE!");
		this->drawString(10, 20, "RESULTS:");
		this->drawString(10, 28, showPlayerScores().c_str());

		this->drawString(10, 44, "Press 'x' to continue...");

		glBegin(GL_POLYGON);
		glEnd();

    orthoEnd();
}

string Hud::showPlayerInfo() {
	stringstream info;
	info << "Player:" << playerInfo->id;
	info << " Score:" << playerInfo->getScore();
	return info.str();
}

string Hud::showPlayerScores() {
	stringstream info;
	info << "Total Score: " << playerInfo->getScore();
	return info.str();
}

string Hud::showCameraStats() {
	stringstream stats;
	stats << "Camera Mode: " << camStats->getModeName();
	return stats.str();
}

void Hud::drawPowerBar() {
	
	int y_offset = GLUT_SCREEN_HEIGHT-10;
	int x_offset = 10;

	glColor3f(0.9f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex2f(x_offset, y_offset);
		glVertex2f(barWidth, y_offset);
		glVertex2f(barWidth, ((1 - (playerInfo->getPower()/playerInfo->getMaxPower())) *(y_offset-maxBarHeight)) + maxBarHeight);
		glVertex2f(x_offset, ((1 - (playerInfo->getPower()/playerInfo->getMaxPower())) *(y_offset-maxBarHeight)) + maxBarHeight);
	glEnd();
}