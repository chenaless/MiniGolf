#pragma once
#include <cstring>

#include "Vector3D.h"

class Camera
{
public:
	Camera();
	~Camera();
	string getModeName();
	void setDefaultMode();
	void setFreeMode();
	void setTopViewMode();
	void setToFollow(Vector3D*);
	void rotLeftYAxis();
	void rotRightYAxis();
	void rotDownXAxis();
	void rotUpXAxis();
	void run();
private:
	int mode;
	float xrot;
	float yrot;
	float backup; // default backup dist from object
	float tilt; // default view tilt
	Vector3D *follow;
};

