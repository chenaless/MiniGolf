#pragma once

#include "Vector3D.h"
#include "Ball.h"
#include "Tile.h"

class Physics
{
public:
	Physics();
	~Physics();
	void applyGravity(Ball*, Tile*);
	void applyBallPhysics(Ball*, Tile*);
	bool collision(Vector3D, Vector3D, float, float); // for sphere-sphere collision
private:
	void handleBallWallCollision(Ball*, Tile*);
	bool isHeadingThisWall(Ball*, Tile*, const int &);
	float distRayPlane(Vector3D , Vector3D , Vector3D , float );
	void calcSlopeDirection(Ball*, Tile*);
	Vector3D worldUp;
	float gravity;
	float rollFric;
	float airDrag;
	float minVelocity;
	float maxVelocity;
};

