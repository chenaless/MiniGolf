#pragma once

#include "Overlay.h"
#include "Player.h"

class MenuScreen : public Overlay
{
public:
	MenuScreen();
	MenuScreen(Player*);
	~MenuScreen();
	void draw(const int &); // edit this
	int drawLevelSelection(const int &);
	void setPlayerProfile(Player* p);
	void showTopScore();
private:
	Player* playerInfo;
	int maxLevels;
	string pickLevel(const int &);
};

