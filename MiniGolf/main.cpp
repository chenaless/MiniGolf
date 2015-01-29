#include "Vector3D.h"
#include "Camera.h"
#include "Hud.h"
#include "Level.h"
#include "Shader.h"
#include "Util.h"
#include "Player.h"
#include "InputManager.h"
#include "MenuScreen.h"

#include <string>
#include <iostream>
#include <list>
#include <GL/glew.h>
#include <GL/glut.h>

using namespace std;

Shader* shader;
char** levels;
Level** minigolf;
Camera* cam;
Player* player1;
InputManager* input;
MenuScreen* menu;
Hud* hud;

enum GameState {
	MENU = 0,
	PLAY = 1,
	RESULTS = 2,
	LOAD = 3,
};

GameState gameState;

int lastLevel;
int currlvl = 0;

void enable() {
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_NORMALIZE );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable( GL_COLOR_MATERIAL );
}

void initialize(const int &numlvls, char** lvl) {
	// create and load shader programs
	shader = new Shader("shader.vert", "shader.frag");
	shader->bind();

	lastLevel = numlvls;

	// store level data filenames
	levels = new char*[lastLevel];
	for (int i = 0; i < lastLevel; i++) {
		levels[i] = new char[strlen(lvl[i+1] +1)];
		levels[i] = lvl[i+1];
	}

	// load levels
	minigolf = new Level*[lastLevel];
	for (int i = 0; i < numlvls; i++) {
		minigolf[i] = new Level();
		minigolf[i]->load(levels[i]);
	}

	// load game contents (clean the objects up at end)
	cam = new Camera();

	player1 = new Player(1);

	input = new InputManager(cam, minigolf[currlvl], player1);

	menu = new MenuScreen(player1);

	hud = new Hud(player1, cam);

	gameState = MENU;
}

void keyboard(unsigned char key, int x, int y) {
	if (gameState == MENU) {

		switch (key) {
			// Level Selection
			case 'm': // up
				if (currlvl < (lastLevel-1))
					currlvl++;
				break;
			case 'n': // down
				if ((currlvl-1) >= 0)
					currlvl--;
				break;
			case 'x': // done w/selection
				currlvl--; // for loading offset
				gameState = LOAD;
				break;
		}

	} else if (gameState == PLAY) {

		input->handleCameraKey(key);
		input->handleGameplayKey(key);

	} else if (gameState == RESULTS) {

		switch (key) {
			// load next level
			case 'x':
				gameState = LOAD;
				break;
		}

	}

	// General Controls
	if (key == 27)
		exit(0); // edit to cleaner termination

} 

void keyboardUp(unsigned char key, int x, int y) {
	if (gameState == PLAY) {
		input->handleGameplayKeyUp(key);
	}
}

void update() {
	if (gameState == PLAY) { // play game

		minigolf[currlvl]->update();
		if (minigolf[currlvl]->wonGame())
			gameState = RESULTS;

	} else if (gameState == LOAD) { // load next level

		currlvl++;
		if (currlvl == lastLevel)
			currlvl = 0;
		player1->resetScore();
		cam->setDefaultMode();
		if (input)
			delete input;
		input = new InputManager(cam, minigolf[currlvl], player1);
		gameState = PLAY;

	}
}

void display() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();

	if (gameState == MENU) {

		menu->draw(currlvl); // edit this

	} else if (gameState == PLAY) {

		glPushMatrix();
			cam->run();

			minigolf[currlvl]->draw();

			drawAxis3D();
		glPopMatrix();

		hud->draw();

	} else if (gameState == RESULTS) {

		hud->drawResults();
		// show results

	} else if (gameState == LOAD) {

		// render loadind screen

	}

	glFlush();
    glutSwapBuffers();

	update();
}

void reshape (int w, int h) {
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void timerGL(int val) {
	glutPostRedisplay();
	//cout << "tick: " << val << endl; // val displayed every 50 ms
	glutTimerFunc(50, timer, 0); // in milliseconds
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Miniature GLof");
	
	glewInit();
	if (glewIsSupported("GL_VERSION_2_0"))
		printf("Ready for OpenGL 2.0\n");
	else {
		printf("OpenGL 2.0 not supported\n");
		exit(1);
	}

	enable();

	// -1 to omit the executable name
	initialize((argc - 1), argv);

    glutDisplayFunc(display);
    glutIdleFunc(display);
	glutTimerFunc(0, timerGL, 0);
    glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
    
	glutMainLoop();

    return 0;
}