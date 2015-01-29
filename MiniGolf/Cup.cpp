#include "Cup.h"
#include "Math.h"
#include <iostream>
#include <cmath>

using namespace std;

static float black[] = {0.0f, 0.0f, 0.0f};

Cup::Cup(char *info) : radius(0.06) {
	info = strtok (NULL, " ");
	try {
		tileID = atoi(info); // get id
		info = strtok (NULL, " ");
		pos.x = (float)atof(info); // get x
		info = strtok (NULL, " ");
		pos.y = (float)atof(info); // get y
		info = strtok (NULL, " ");
		pos.z = (float)atof(info); // get z
		info = strtok (NULL, " ");
	} catch (runtime_error e) {
		cerr << e.what() << endl;
		exit(1);
	}

}

Cup::~Cup() {
}

void Cup::draw() {

	int smoothness = 20;
	float y_offset = 0.001; // to make hole visible
	glColor3f(0, 0, 0);

	glPushMatrix();

		glBegin(GL_TRIANGLES);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
			for(unsigned i = 0; i < smoothness; i++)
			{
				float theta1 = i * 2 * PI / smoothness;
				float theta2 = (i + 1) * 2 * PI / smoothness;

				Vector3D p1((float)(cos(theta1)*radius+pos.x), pos.y, (float)(sin(theta1)*radius+pos.z));
				Vector3D p2((float)(cos(theta2)*radius+pos.x), pos.y, (float)(sin(theta2)*radius+pos.z));

				if(i == 0)
				{
					Vector3D u = p1-pos;
					Vector3D v = p2-pos;
					Vector3D norm = u.cross(v);
					glNormal3f(norm.x, norm.y, norm.z);
				}

				glVertex3f(pos.x, pos.y+y_offset, pos.z);
				glVertex3f(p1.x, p1.y+y_offset, p1.z);
				glVertex3f(p2.x, p2.y+y_offset, p2.z);
			}
		glEnd();

	glPopMatrix();
}

int Cup::getTileId() {
	return tileID;
}

float Cup::getRadius() {
	return radius;
}