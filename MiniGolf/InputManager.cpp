#include "InputManager.h"


InputManager::InputManager() : cam(NULL), lvl(NULL), pl(NULL) {
}

InputManager::InputManager(Camera* link_cam, Level* link_lvl, Player* link_pl) {
	cam = link_cam;
	lvl = link_lvl;
	pl = link_pl;
}

InputManager::~InputManager() {
	// pointed objects will delete itself
	cam = NULL;
	lvl = NULL;
	pl = NULL;
}

// Player/Ball Controls
void InputManager::handleGameplayKey(const char &key) {
	if (!lvl->getBall()->isMoving) {
		switch (key) {
			case 'n': // rotate CCW
				lvl->getBall()->rotateLeft();
				cout << lvl->getBall()->dir << endl;
				break;
			case 'm': // rotate CW
				lvl->getBall()->rotateRight();
				break;
			case 'p': // charge power
				if (!lvl->getBall()->isMoving)
					pl->charge();
				break;
		}
	}
}

void InputManager::handleGameplayKeyUp(const char &key) {
		if (!lvl->getBall()->isMoving) {
			switch (key) {
				case 'p':
					pl->strike(lvl->getBall());
					break;
			}
		}
}

// Camera Control/Modes
void InputManager::handleCameraKey(const char &key) {
	switch (key) {
		case '1':
			cam->setDefaultMode();
			break;

		case '2':
			cam->setFreeMode();
			break;

		case '3':
			cam->setTopViewMode();
			break;

		case '4':
			cam->setToFollow(&lvl->getBall()->pos);
			break;

		// (Free Mode Only)
		case 'a': // left
			cam->rotLeftYAxis();
			break;
		case 'd': // turn right
			cam->rotRightYAxis();
			break;
		case 'w': // tilt up
			cam->rotUpXAxis();
			break;
		case 's': // tilt down
			cam->rotDownXAxis();
			break;
	}
}

void InputManager::handleMenuKey(const char &key) {
	/*
	switch (key) {
		// Level Selection
		case ',': // up
			break;
		case '.': // down
			break;
		case 'x': // done w/selection
			gameState = PLAY;
			break;
	}
	*/
}