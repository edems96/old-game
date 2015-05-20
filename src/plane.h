#ifndef PLANE_H
#define PLANE_H

#include "vector3f.h"

class Plane {
	public:
		Plane(const vector3f p1, const vector3f p2, const vector3f p3, const vector3f p4);
		Plane(vector3f verticles[4]);
		
		vector3f verticles[4];
		vector3f normal;
		
	private:
		void calculateNormal( void );
};

#endif