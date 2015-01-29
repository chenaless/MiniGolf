#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

using namespace std;

class Vector3D {
public:
	Vector3D();
	~Vector3D();
	Vector3D(const Vector3D &);
	Vector3D(const float &, const float &, const float &);
	
	friend ostream& operator<< (ostream &, Vector3D &);
	Vector3D &operator=(const Vector3D &);
	Vector3D &operator*=(const float &);
	Vector3D &operator/=(const float &);
	Vector3D operator -() const;
	Vector3D operator+(const Vector3D &);
	Vector3D operator-(const Vector3D &);
	Vector3D operator*(const Vector3D &);
	Vector3D operator*(const float &);
	Vector3D operator/(const float &);
	bool operator<=(const float &);

	Vector3D absolute();
	void normalize();
	Vector3D cross(const Vector3D &);
	float dot(const Vector3D &);
	void set(const GLfloat &, const GLfloat &, const GLfloat &);

	float x;
	float y;
	float z;
private:
};