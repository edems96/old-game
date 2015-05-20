#include "plane.h"

Plane::Plane(const vector3f p1, const vector3f p2, const vector3f p3, const vector3f p4) {
	verticles[0] = p1;
	verticles[1] = p2;
	verticles[2] = p3;
	verticles[3] = p4;
	
	calculateNormal();
}


Plane::Plane(vector3f verticles[4]) {
	//this->verticles = verticles;
	
	this->verticles[0] = verticles[0];
	this->verticles[1] = verticles[1];
	this->verticles[2] = verticles[2];
	this->verticles[3] = verticles[3]; 
	
	calculateNormal();
}

void Plane::calculateNormal( void ) {
	normal = (verticles[1]-verticles[0]).crossProduct(verticles[2]-verticles[0]).normalize();
	printf("Normal: %s\n", normal.toChars());
}