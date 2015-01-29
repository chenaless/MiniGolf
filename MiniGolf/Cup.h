#pragma once
#include "GameObject.h"
#include "Vector3D.h"

class Cup : public GameObject
{
public:
	Cup(char*);
	~Cup();
	void draw();
	int getTileId();
	float getRadius();
	Vector3D pos;	
private:
	float radius;
	int tileID;
};

