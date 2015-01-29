#include "Tee.h"

#include <iostream>

using namespace std;

Tee::Tee(char *info) : rad(0.15) {
	info = strtok (NULL, " ");
	try {
		tileID = atoi(info); // get id
		info = strtok (NULL, " ");
		coord.x = atof(info); // get x
		info = strtok (NULL, " ");
		coord.y = atof(info); // get y
		info = strtok (NULL, " ");
		coord.z = atof(info); // get z
		info = strtok (NULL, " ");
	} catch (runtime_error e) {
		cerr << e.what() << endl;
		exit(1);
	}
}

Tee::~Tee()
{
}

void Tee::draw() {
	float y_offset = 0.001; // to enable visibility above tile
	glPushMatrix();
		glColor3f(0, 0, 1.0f);
		glTranslatef(coord.x, coord.y, coord.z);
		glBegin(GL_QUADS); // Start drawing a point primitive  
			glVertex3f(-rad, 0+y_offset, -rad);
			glVertex3f(rad, 0+y_offset, -rad);
			glVertex3f(rad, 0+y_offset, rad);
			glVertex3f(-rad, 0+y_offset, rad);
		glEnd();
	glPopMatrix();
}

Vector3D Tee::getCoord() const {
	return coord;
}

int Tee::getTileID() const {
	return tileID;
}