#pragma once

#include "Camera.h"
#include "Level.h"
#include "Player.h"

class InputManager
{
public:
	InputManager();
	InputManager(Camera*, Level*, Player*);
	~InputManager();
	void handleGameplayKey(const char &);
	void handleGameplayKeyUp(const char &);
	void handleCameraKey(const char &);
	void handleMenuKey(const char &);
private:
	Camera* cam;
	Level* lvl;
	Player* pl;
};

