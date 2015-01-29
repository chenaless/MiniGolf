#pragma once
#include <string>

#include "Vector3D.h"

// tile type for collision handling
enum TileCollision
{
	Grass = 0,
	Sand = 1,
	Water = 2,
};

class Tile {
public:
	Tile();
	Tile(char *info);
	~Tile();
	void draw();
	void drawEdges(); // in case if we don't want to see edge borders ;)
	GLfloat* normalize(const GLfloat*);
	int numsides;
	int *edges; // index in relation bottom left CCW
	Vector3D *edge_normals;
	float *edge_dist; // from Ax + By + Cz + D = 0, normal <A, B, C> with distance D.
	Vector3D *coords; // tile vertices
	Vector3D normal;
private:
	void calcNormal();
	void calcEdgeNormals();
	void calcEdgeDist();
	void drawNormal(); // for debugging
	void drawEdgeNormals(); // for debugging
	TileCollision type;
};