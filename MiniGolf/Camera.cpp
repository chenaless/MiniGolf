#include "Camera.h"
#include "Util.h"

#include <GL/glew.h>
#include <GL/glut.h>

enum Mode {
	DEFAULT = 0,
	FREE = 1,
	TOP = 2,
	FOLLOW = 3,
};

// keep track of x/z-plane for now

Camera::Camera() : xrot(0), yrot(0), backup(-8.0f), tilt(30.0f), follow(new Vector3D()) {
	setDefaultMode();
}

Camera::~Camera() {
	// we do not want to delete followed object, as it's own
	// destructor will take care of self cleanup (else it'll crash)
	follow = NULL;
}

string Camera::getModeName() {
	string name;
	switch (mode) {
		case 0:
			name = "Default";
			break;
		case 1:
			name = "Free";
			break;
		case 2:
			name = "Top";
			break;
		case 3:
			name = "Follow";
			break;
	}
	return name;
}

void Camera::run() {
	
	glTranslatef(0.0, 0.0, backup);
	glRotatef(tilt, 1.0, 0.0, 0.0);

	if (mode == DEFAULT) {
		// do nothing
	} else if (mode == FREE) {
		glRotatef(yrot, 0.0, 1.0, 0.0);
		glRotatef(xrot, 1.0, 0.0, 0.0);
	} else if (mode == TOP) {
		glRotatef((GLfloat)yrot, 0.0, 1.0, 0.0);
		glRotatef((GLfloat)xrot, 1.0, 0.0, 0.0);
	} else if (mode == FOLLOW) {
		glTranslatef(0.0, -2.0f, -2.0f);
		glRotatef(20.0f, 1.0, 0.0, 0.0);
		glTranslatef(-follow->x, follow->y, -follow->z);
	}

}

void Camera::setDefaultMode() {
	xrot = 0.0;
	yrot = 0.0;
	mode = DEFAULT;
}

void Camera::setFreeMode() {
	mode = FREE;
}

void Camera::setTopViewMode() {
	yrot = 0;
	xrot = 90 - tilt;
	mode = TOP;
}

void Camera::setToFollow(Vector3D* vec) {
	follow = vec;
	mode = FOLLOW;
}

void Camera::rotLeftYAxis() {
	if (mode == FREE)
		yrot--;
}

void Camera::rotRightYAxis() {
	if (mode == FREE)
		yrot++;
}

void Camera::rotDownXAxis() {
	if (mode == FREE)
		xrot++;
}

void Camera::rotUpXAxis() {
	if (mode == FREE)
		xrot--;
}
