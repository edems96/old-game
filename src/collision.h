#ifndef COLLISION_H
#define COLLISION_H

#include <cmath>

#include "cube.h"
#include "vector3f.h"

class Collision {
	public:
		static float square(float n);
		static float triangleArea(vector3f p1, vector3f p2, vector3f p3);
		static float pointDistance(vector3f p1, vector3f p2);
		static float pointDistanceSquare(vector3f p1, vector3f p2);
		
		static bool raySphere(const vector3f start, const vector3f direction, const vector3f sphereOrigin, float sphereRadius, float* dist, vector3f* collisionPoint);
		static bool rayPlane(vector3f start, vector3f direction, vector3f normal, vector3f p1, vector3f p2, vector3f p3, vector3f p4, float* dis, vector3f* point);
		static bool spherePlane(vector3f& sphereOrigin, float radius, vector3f normal, vector3f p1, vector3f p2, vector3f p3, vector3f p4);
		static bool sphereSphere(vector3f& sphereOrigin1, float sphereRadius1, vector3f& sphereOrigin2, float sphereRadius2);

		static bool sphereCube(vector3f& start, float radius, Cube cube);
};

#endif