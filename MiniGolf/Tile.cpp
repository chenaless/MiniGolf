#include "Tile.h"
#include "Util.h"

#include <iostream>
#include <cstdio>
#include <cmath>
#include <GL/glew.h>
#include <GL/glut.h>

using namespace std;

// for display list
GLuint displist;

// PRECOND: User must provide object data in correct format, as shown in CS164's Lab1 input samples.
// POSTCOND: Loads object data from format: [ID][coord3D]

// PRECOND: User must provide tile data in correct format, as shown in CS164's Lab1 input samples.
// POSTCOND: Loads tile data from format: [ID][#sides][coords3D][neighborID, starting w/lower-left corner]
Tile::Tile(char *info) {
	info = strtok (NULL, " ");
	try {
		numsides = atoi(info); // get num sides
		coords = new Vector3D[numsides];
		edges = new int[numsides];
		edge_normals = new Vector3D[numsides];
		edge_dist = new float[numsides];

		// get n-coords, one coord3D at a time
		info = strtok (NULL, " ");
		for (int i = 0; i < numsides; i++) {
			coords[i].x = atof(info); // get x
			info = strtok (NULL, " ");
			coords[i].y = atof(info); // get y
			info = strtok (NULL, " ");
			coords[i].z = atof(info); // get z
			info = strtok (NULL, " ");
		}

		// collect edge data (for later use)
		for (int e = 0; e < numsides; e++) {
			edges[e] = atoi(info);
			info = strtok (NULL, " ");
		}

		// set tile normal & get edge normals
		calcNormal();
		calcEdgeNormals();

	} catch (runtime_error e) {
		cerr << e.what() << endl;
		exit(1);
	}
}

Tile::~Tile() {
	if (coords)
		delete[] coords;
	coords = NULL;

	if (edges)
		delete[] edges;
	edges = NULL;

	if (edge_normals)
		delete[] edge_normals;
	edge_normals = NULL;

	if (edge_dist)
		delete[] edge_dist;
	edge_dist = NULL;
}

void Tile::drawEdges() {
	glPushMatrix();
		glColor3f(0.5f, 0.35f, 0.05f); // brown
		glLineWidth(3.0f);
		glBegin(GL_LINES);

			// draw edges, where n = from, n+1 = to
			for (int n = 0; n < numsides; n++) {
				if (edges[n] == 0) { // edge is not connected to another tile
					glVertex3f(coords[n].x, coords[n].y, coords[n].z);
					if (n+1 != numsides)
						glVertex3f(coords[n+1].x, coords[n+1].y, coords[n+1].z);
					else // wrap edge from end->start
						glVertex3f(coords[0].x, coords[0].y, coords[0].z);
				}
			}

		glEnd();
		glLineWidth(1.0f); // reset to default
	glPopMatrix();
}

void Tile::drawNormal() {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	for (int n = 0; n < numsides; n++) {
		x += coords[n].x;
		y += coords[n].y;
		z += coords[n].z;
	}

	x /= numsides;
	y /= numsides;
	z /= numsides;

	float scale = 0.6f;
	float nx = x + (normal.x * scale);
	float ny = y + (normal.y * scale);
	float nz = z + (normal.z * scale);

	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
			glVertex3f(x, y, z);
			glVertex3f(nx, ny, nz);
		glEnd();
	glPopMatrix();
}

void Tile::drawEdgeNormals() {
	float x, y, z;
	float nx, ny, nz;
	float scale = 0.2;
	float y_offset = 0.001; // to draw above tile

	for (int e = 0; e < numsides; e++) {
		if ((e+1) == numsides) {
			x = (coords[e].x + coords[0].x) / 2.0;
			y = (coords[e].y + coords[0].y) / 2.0;
			z = (coords[e].z + coords[0].z) / 2.0;
		} else {
			x = (coords[e].x + coords[e+1].x) / 2.0;
			y = (coords[e].y + coords[e+1].y) / 2.0;
			z = (coords[e].z + coords[e+1].z) / 2.0;
		}

		nx = x + (edge_normals[e].x * scale);		
		ny = y + (edge_normals[e].y * scale);	
		nz = z + (edge_normals[e].z * scale);	

		glPushMatrix();
			glColor3f(0.0f, 0.0f, 1.0f);
			glBegin(GL_LINES);
				glVertex3f(x, (y+y_offset), z);
				glVertex3f(nx, (ny+y_offset), nz);
			glEnd();
		glPopMatrix();
	}
}

void Tile::draw() {
	//displist = glGenLists(1);
	glPushMatrix();
		glColor3f(0.0f, 0.6f, 0.0f);
		glBegin(GL_POLYGON);
			// foreach coords
			for (int i = 0; i < numsides; i++) {
				glNormal3f(normal.x, normal.y, normal.z);
				glVertex3f(coords[i].x, coords[i].y, coords[i].z);
			}
		glEnd();
	glPopMatrix();
	//glEndList();
	
	drawNormal();
	drawEdgeNormals();
}

GLfloat* Tile::normalize(const GLfloat* src) {
	float d = 0.0;
	float norm[3] = {src[0], src[1], src[2]};
	
	for (int i = 0; i < 3; i++)
		d += (src[i] * src[i]);

	d = sqrt(d);

	if (d > 0.0) {
		for (int i = 0; i < 3; i++)
			norm[i] /= d;
	}
	return norm;
}

// in courtesy of NeHe Gamedev :), calculates the normal vector based
// on loaded tile data, then stores it in this tile's V3D normal
void Tile::calcNormal() {
	// all points in a tile lie on the same plane, hence the calculated normal should be as well
	float v1[3], v2[3]; // Vector 1 (x,y,z) & Vector 2 (x,y,z)
	int x = 0;
	int y = 1;
	int z = 2;

	// Calculate The Vector From Point 1 To Point 0
	v1[x] = coords[0].x - coords[1].x;
	v1[y] = coords[0].y - coords[1].y;
	v1[z] = coords[0].z - coords[1].z;

	// Calculate The Vector From Point 2 To Point 1
	v2[x] = coords[1].x - coords[2].x;
	v2[y] = coords[1].y - coords[2].y;
	v2[z] = coords[1].z - coords[2].z;

	// Compute The Cross Product To Give Us A Surface Normal
	normal.x = v1[y]*v2[z] - v1[z]*v2[y];
	normal.y = v1[z]*v2[x] - v1[x]*v2[z];
	normal.z = v1[x]*v2[y] - v1[y]*v2[x];

	// normalize the normal vector
	normal.normalize();
}

void Tile::calcEdgeNormals() {
	Vector3D up = Vector3D(0, 1.0f, 0);
	Vector3D dir;

	for (int e = 0; e < numsides; e++) {
		if ((e+1) == numsides) {
			dir = coords[0] - coords[e];
		} else {
			dir = coords[e+1] - coords[e];
		}
		Vector3D n = up.cross(dir);
		n.normalize();
		edge_normals[e] = n;
		//cout << "ENorm: " << edge_normals[e] << endl; // DEBUG
	}

	calcEdgeDist();
}

void Tile::calcEdgeDist() {
	for (int e = 0; e < numsides; e++) {
		edge_dist[e] = edge_normals[e].dot(coords[e]);
		//cout << "PlaneD: " << edge_dist[e] << endl;
	}
}
