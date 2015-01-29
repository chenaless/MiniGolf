#pragma once
#include <GL/glew.h>
#include <GL/glut.h>

class Overlay
{
public:
	Overlay();
	virtual ~Overlay();
	virtual void draw() {}
protected:
	void orthoBegin();
	void orthoEnd();
	void drawString(float, float, const char*);
};

