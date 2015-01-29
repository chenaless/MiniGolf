// distRayPlane credit goes to:
// www.gamespp.com/algorithms/collisionDetectionTutorial02.html
#include "Physics.h"
#include "Util.h"

#include <iostream>
#include <cmath>

Physics::Physics() {
	gravity = -0.0098;
	worldUp = Vector3D(0, 1 , 0);
	rollFric = 0.998f;
	minVelocity = 0.0006f;
	//maxVelocity = 0.0001f;
}

Physics::~Physics() {
}

void Physics::applyGravity(Ball *b, Tile *tile) {
	// if (sweep(dist ball-ground > 0))
		// v = vnot + gt, F = mg
		//b->vel.y = b->vel.y + gravity;
}

void Physics::applyBallPhysics(Ball *b, Tile* tile) {
	// get tile friction/bounds, normals, etc. from tile
	calcSlopeDirection(b, tile);

	if (b->isMoving) {

		//applyGravity(b, tile);

		b->vel *= rollFric;
		b->pos = b->pos + (b->vel * b->dir);
		
		if (b->vel.absolute() <= minVelocity) { // ignore reverse rolling for now, to prevent in
			b->isMoving = false;
			//b->recharge();
		}

		handleBallWallCollision(b, tile);
	}
}

bool Physics::collision(Vector3D p1, Vector3D p2, float r1, float r2) {
	float dist = sqrt(((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y)) + ((p1.z - p2.z) * (p1.z - p2.z)));
	if (dist <= r2) {
		return true;
	}
	return false;
}

void Physics::handleBallWallCollision(Ball *b, Tile* tile) {
	for (int e = 0; e < tile->numsides; e++) {
			
		// closing into this wall
		if (isHeadingThisWall(b, tile, e)) {
			//cout << "Heading to wall(s) " << e << endl; // DEBUG
				
			// dist between wall-ball
			float dist = tile->edge_dist[e] - tile->edge_normals[e].dot(b->pos);
			//cout << "Distance to wall " << e << ": " << dist << endl; // DEBUG

			// look-ahead sweep check for fast moving ball
			Vector3D nextpos = b->pos + (b->vel * rollFric * b->dir);
			float sweep = tile->edge_dist[e] - tile->edge_normals[e].dot(nextpos);

			if (sweep > 0.0) {
				// cout << "Collision at Wall " << e << "!" << " Sweep value: " << sweep << endl; // DEBUG
				if (tile->edges[e] == 0) { // is a wall
					// Bounce: R = 2*(I dot N)*N - I
					Vector3D bounce = Vector3D(b->dir.x, 0.0, b->dir.z); // y is zero b/c we don't want to bounce off the slope
					bounce = ((tile->edge_normals[e] * 2 * b->dir.dot(tile->edge_normals[e])) - b->dir) * -1;
					b->dir = Vector3D(bounce.x, b->dir.y, bounce.z);
				} else { // goto next tile
					b->tileID = tile->edges[e];
					cout << "to tile " << b->tileID << endl; // DEBUG
				}
				break;
			}
		}
	}
}

bool Physics::isHeadingThisWall(Ball *b, Tile *tile, const int &id) {
	float d = distRayPlane(b->pos, b->dir, tile->edge_normals[id], tile->edge_dist[id]);
	if (d > 0.0)
		return true;
	return false;
}

// find the distance between a ray and a plane.
float Physics::distRayPlane(Vector3D vRayOrigin, Vector3D vnRayVector, Vector3D vnPlaneNormal, float planeD)
{
    float cosAlpha;
    float deltaD;

    cosAlpha = vnRayVector.dot(vnPlaneNormal);

    // parallel to the plane (alpha=90)
    if (cosAlpha == 0) -1.0f;

    deltaD = planeD - vRayOrigin.dot(vnPlaneNormal);
    
	return (deltaD/cosAlpha);
}

void Physics::calcSlopeDirection(Ball *b, Tile *tile) {
	Vector3D xaxis = worldUp.cross(tile->normal);
	Vector3D slope = tile->normal.cross(xaxis);

	slope.normalize();

	//cout << slope.y << ":"; // DEBUG SLOPE

	if (slope.y != 0.0) {
		if (tile->normal.dot(b->dir) > 0.0) { // rolling down
			b->dir.y = slope.y * -1;
		} else if (tile->normal.dot(b->dir) < 0.0) { // rolling up
			b->dir.y = slope.y;
		} else {
		}
	} else {
		b->dir.y = 0.0; 
	}
}