// shader credit goes to:
// www.lighthouse3d.com/opengl/glsl/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/glut.h>

class Shader {
public:
	Shader();
	Shader(char*, char*);
	~Shader();
	void bind();
	void unbind();
private:
	char* readTextFile(char*);
	int textFileWrite(char*, char*);
	void printShaderInfoLog(GLuint);
	void printProgramInfoLog(GLuint);
	GLuint prog;
	GLuint vert;
	GLuint frag;
};
