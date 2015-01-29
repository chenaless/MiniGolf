#include "Util.h"

// thanks to cplusplus.com :)
void timer(int milliseconds) {
	clock_t endwait;
	endwait = clock() + milliseconds * CLOCKS_PER_SEC * (0.001);
	while (clock() < endwait) {}
}

// Draws string at position x, y, z
void draw_string(float x, float y, float z, char *txt) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glDisable(GL_LIGHTING);

	glPushMatrix();
		glRasterPos3f( x, y, z );
		while( *txt != '\0' ) {
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, *txt );
			txt++;
		}
	glPopMatrix();

	glEnable(GL_LIGHTING);
}

// Draws string at posarray x, y, z
void draw_string(float* coord, char *txt) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glDisable(GL_LIGHTING);

	glPushMatrix();
		glRasterPos3fv(coord);
		while( *txt != '\0' ) {
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, *txt );
			txt++;
		}
	glPopMatrix();

	glEnable(GL_LIGHTING);
}

void drawAxis3D() {
	float scale = 1.5;
	float origin[3] = {0.0, 0.0, 0.0};
	float axis[3][3] = {{1.0, 0.0, 0.0},
						{0.0, 1.0, 0.0},
						{0.0, 0.0, 1.0}};
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glDisable(GL_LIGHTING);

	glPushMatrix();
		glBegin(GL_LINES);
			for (int i = 0; i < 3; i++) {
				glVertex3fv(origin);
				glVertex3fv(axis[i]);
			}
		glEnd();
	glPopMatrix();

	draw_string(axis[0], "+x");
	draw_string(axis[1], "+y");
	draw_string(axis[2], "+z");

	glEnable(GL_LIGHTING);
}