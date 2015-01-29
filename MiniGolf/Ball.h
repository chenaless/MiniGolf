#pragma once

#include "Vector3D.h"

class Ball
{
public:
	Ball();
	Ball(const Vector3D &, int);
	~Ball();
	void draw();
	void drawDirection();
	void push(float &);
	void rotateLeft();
	void rotateRight();
	void recharge();
	Vector3D pos; // position
	Vector3D vel; // velocity
	Vector3D dir; // direction
	int tileID;
	float getRadius();
	bool isMoving;
	bool isOnGround;
private:
	void rotateYAxis();
	float vnot; // initial velocity
	float radius;
	int angle; // rotation angle
};

