#pragma once

#include "Overlay.h"
#include "Player.h"
#include "Camera.h"

class Hud : public Overlay {
public:
	Hud(Player*, Camera*);
	~Hud();
	void draw();
	void drawResults();
private:
	Player* playerInfo;
	Camera* camStats;
	string showPlayerInfo();
	string showPlayerScores();
	string showCameraStats();
	void drawPowerBar();
	int barWidth;
	int maxBarHeight;
};

