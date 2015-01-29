#include "Vector3D.h"

#include <cmath>

Vector3D::Vector3D() : x(0), y(0), z(0) {
}

Vector3D::~Vector3D() {
}

Vector3D::Vector3D(const Vector3D &other) {
	x = other.x;
	y = other.y;
	z = other.z;
}

Vector3D::Vector3D(const float &nx, const float &ny, const float &nz) {
	x = nx;
	y = ny;
	z = nz;
}

// operator overloading
ostream& operator<<(ostream &out, Vector3D &vec) {
	out << "<" << vec.x << "," << vec.y << "," << vec.z << ">";
	return out;
}

Vector3D& Vector3D::operator=(const Vector3D &other) {
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

Vector3D& Vector3D::operator*=(const float &rhs) {
	*this = (*this) * rhs;
	return *this;
}

Vector3D& Vector3D::operator/=(const float &rhs) {
	*this = (*this) / rhs;
	return *this;
}

Vector3D Vector3D::operator-() const {
	Vector3D ans;
	ans.x = -x;
	ans.y = -y;
	ans.z = -z;
	return ans;
}

Vector3D Vector3D::operator+(const Vector3D &other) {
	Vector3D ans;
	ans.x = x + other.x;
	ans.y = y + other.y;
	ans.z = z + other.z;
	return ans;
}

Vector3D Vector3D::operator-(const Vector3D &other) {
	Vector3D ans;
	ans.x = x - other.x;
	ans.y = y - other.y;
	ans.z = z - other.z;
	return ans;
}

Vector3D Vector3D::operator*(const Vector3D &other) {
	Vector3D ans;
	ans.x = x * other.x;
	ans.y = y * other.y;
	ans.z = z * other.z;
	return ans;
}

Vector3D Vector3D::operator*(const float &multip) {
	Vector3D ans;
	ans.x = x * multip;
	ans.y = y * multip;
	ans.z = z * multip;
	return ans;
}

Vector3D Vector3D::operator/(const float &divisor) {
	Vector3D ans;
	if (divisor != 0) {
		if (x == 0) {
			ans.x = 0;
		} else {
			ans.x = x / divisor;
		}
		if (y == 0) {
			ans.y = 0;
		} else {
			ans.y = y / divisor;
		}
		if (z == 0) {
			ans.z = 0;
		} else {
			ans.z = z / divisor;
		}
	} else if (ans.x == 0 && ans.y == 0 && ans.z == 0 && divisor == 0) {
		ans = Vector3D(0, 0, 0);
	} else {
		cerr << "Error: vector division by zero." << endl;
		exit(1);
	}
	return ans;
}

// solely made to compare against zero, may make Vec3.Zero() in future
bool Vector3D::operator<=(const float &num) {
	return (x <= num && y <= num && z <= num);
}

Vector3D Vector3D::absolute() {
	return Vector3D(abs(x), abs(y), abs(z));
}

Vector3D Vector3D::cross(const Vector3D &other) {
	Vector3D ans;
	// Compute The Cross Product To Give Us A Surface Normal
	ans.x = ((*this).y * other.z) - ((*this).z * other.y);
	ans.y = ((*this).z * other.x) - ((*this).x * other.z);
	ans.z = ((*this).x * other.y) - ((*this).y * other.x);
	return ans;
}

float Vector3D::dot(const Vector3D &other) {
	//float ans = (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
	return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
}

void Vector3D::normalize() {
	float d = (x * x) + (y * y) + (z * z);
	d = (float)sqrt(d);
	(*this) = (*this) / d;
}

void Vector3D::set(const float &nx, const float &ny, const float &nz) {
	x = nx;
	y = ny;
	z = nz;
}
