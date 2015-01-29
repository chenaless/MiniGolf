#include "Ball.h"
#include "Math.h"

#include <cmath>

Ball::Ball() {
}

Ball::Ball(const Vector3D &newpos, int tile)
	: pos(newpos), tileID(tile), vnot(0.0f), radius(0.05f), angle(0) {
	
	isMoving = false;
	isOnGround = true;

	// ALTERNATIVE: depending on pos, find & set tileID
	vel = Vector3D(vnot, vnot, vnot);
	dir = Vector3D(0, 0, -1);
}

Ball::~Ball()
{
}

void Ball::draw() {
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		glTranslatef(pos.x, pos.y+(radius), pos.z);
		glutSolidSphere(radius, 12, 12);
	glPopMatrix();
}

void Ball::drawDirection() {
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		glBegin(GL_LINES);
			glVertex3f(pos.x, pos.y+0.001, pos.z);
			glVertex3f(pos.x+dir.x, pos.y+dir.y+0.001, pos.z+dir.z);
		glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Ball::push(float &newvel) {
	if (!isMoving) {
		//cout << newvel << endl;
		vnot = newvel;
		recharge();
		isMoving = true;
	}
}

void Ball::rotateYAxis() {
	float t = degToRad((float)(angle * 0.1));
	dir.x = (dir.x * cos(t)) + (dir.z * sin(t));
	dir.z = (dir.z * cos(t)) - (dir.x * sin(t));
	dir.normalize();
}

void Ball::rotateLeft() {
	angle = (angle + 1) % 360;
	rotateYAxis();
}

void Ball::rotateRight() {
	if (angle == 0)
		angle = 359;
	else
		angle--;
	rotateYAxis();
}

void Ball::recharge() {
	vel = Vector3D(vnot, vnot, vnot);
}

float Ball::getRadius() {
	return radius;
}