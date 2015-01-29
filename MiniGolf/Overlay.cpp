#include "Overlay.h"


Overlay::Overlay()
{
}


Overlay::~Overlay()
{
}

void Overlay::orthoBegin() {
	glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, GLUT_SCREEN_WIDTH, 0, GLUT_SCREEN_HEIGHT);
    glScalef(1, -1, 1);
    glTranslatef(0, -GLUT_SCREEN_HEIGHT, 0);
    glMatrixMode(GL_MODELVIEW);
	glDisable( GL_LIGHTING );
    glLoadIdentity();
}

void Overlay::orthoEnd() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
	glEnable( GL_LIGHTING );
}

void Overlay::drawString(float x, float y, const char *txt) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		glRasterPos2f(x, y);
		while( *txt != '\0' ) {
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, *txt );
			txt++;
		}
	glPopMatrix();
}