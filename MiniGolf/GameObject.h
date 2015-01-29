#pragma once
#include <iostream>

using namespace std;

#include "Vector3D.h"

// move tee & cup here later
class GameObject
{
public:
	GameObject() {}
	virtual ~GameObject() {}
	virtual void draw() {}
protected:
	int tileID; // the id of the tile it's in
	Vector3D coord;
};

