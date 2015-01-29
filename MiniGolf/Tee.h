#pragma once
#include "GameObject.h"

class Tee : public GameObject
{
public:
	Tee(char*);
	~Tee();
	void draw();
	Vector3D getCoord() const;
	int getTileID() const;
private:
	float rad; // half of tee's square to render
};

