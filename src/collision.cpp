#include "collision.h"

float Collision::square(float n) {
	return (n*n);
}

float Collision::triangleArea(vector3f p1, vector3f p2, vector3f p3) {

	float a = sqrt((p2-p1).dotProduct(p2-p1));
	float b = sqrt((p3-p2).dotProduct(p3-p2));
	float c = sqrt((p1-p3).dotProduct(p1-p3));
	
	float s = (a+b+c) / 2.0f;
	
	return sqrt( s * ((s-a) * (s-b) * (s-c)) );
}

float Collision::pointDistance(vector3f p1, vector3f p2) {
	return sqrt(Collision::pointDistanceSquare(p1, p2));
}

float Collision::pointDistanceSquare(vector3f p1, vector3f p2) {
	vector3f vector(p2-p1);
	return (Collision::square(vector.x) + Collision::square(vector.y) + Collision::square(vector.z));
}

bool Collision::raySphere(vector3f start, vector3f direction, vector3f sphereOrigin, float sphereRadius, float* dist, vector3f* collisionPoint) {
	float b = 2 * direction.dotProduct(start - sphereOrigin);
	float c = Collision::square(start.x) - (2*start.x*sphereOrigin.x) + 
			  Collision::square(sphereOrigin.x) + Collision::square(start.y) -
			  (2*start.y*sphereOrigin.y) + Collision::square(sphereOrigin.y) + 
			  Collision::square(start.z) - (2*start.z*sphereOrigin.z) +
			  Collision::square(sphereOrigin.z) - Collision::square(sphereRadius);
		
	float disc = (b*b - 4*c);
		
	if( disc < 0 )
		return false;
		
	if( dist != NULL ) {
		(*dist) = (-b + sqrt(disc)) / 2;
		
		if( collisionPoint != NULL )
			collisionPoint->set(start + direction*(*dist));
	
	}
	
	return true;
}

bool Collision::rayPlane(vector3f start, vector3f direction, vector3f normal, vector3f p1, vector3f p2, vector3f p3, vector3f p4, float* distance, vector3f* point) {
	
	float a = normal.dotProduct(direction);
	if( a == 0 )
		return false;
	
	float t = (normal.dotProduct(p1) - normal.dotProduct(start)) / a;
	
	if( t < 0 )
		return false;
		
	vector3f vector(start + direction*t);
	
	if( 
		std::abs(Collision::triangleArea(p1, p2, p3) - (Collision::triangleArea(p1, p2, vector) + Collision::triangleArea(p2, p3, vector) + Collision::triangleArea(p1, p3, vector))) < 0.3 ||
		std::abs(Collision::triangleArea(p1, p3, p4) - (Collision::triangleArea(p1, p3, vector) + Collision::triangleArea(p3, p4, vector) + Collision::triangleArea(p1, p4, vector))) < 0.3
	) {
		if( distance != NULL ) {
			(*distance) = t;
			
			if( point != NULL )
				point->set(vector);
		}
	
		return true;
	}
	
	return false;
}

bool Collision::spherePlane(vector3f& sphereOrigin, float radius, vector3f normal, vector3f p1, vector3f p2, vector3f p3, vector3f p4) {
	float distance1 = 0;
	float distance2 = 0;
	
	if( 
		Collision::rayPlane(sphereOrigin, normal*(-1), normal, p1, p2, p3, p4, &distance1, NULL) ||
		Collision::rayPlane(sphereOrigin, normal, normal*(-1), p1, p2, p3, p4, &distance2, NULL) ) {
		
		if( distance1 > radius || distance2 > radius ) 
			return false;
			
		if( distance1 > 0 ) 
			sphereOrigin += normal * (radius - distance1);
		else
			sphereOrigin -= normal * (radius - distance2);
			
		return true;
	}
	
	return false;
}

bool Collision::sphereSphere(vector3f& sphereOrigin1, float sphereRadius1, vector3f& sphereOrigin2, float sphereRadius2) {
	float distance = Collision::pointDistanceSquare(sphereOrigin1, sphereOrigin2);
	
	if( distance <= Collision::square(sphereRadius1 + sphereRadius2) ) {
		float a = sqrt(distance) - (sphereRadius1 + sphereRadius2);
		vector3f vector(sphereOrigin2 - sphereOrigin2);
		vector.normalize();
		
		sphereOrigin1 += vector*a;
		
		return true;
	}
	
	return false;
}

bool Collision::sphereCube(vector3f& start, float radius, Cube cube) {
	bool hasCollision = false;

	for(int i = 0; i < cube.planes.size(); i++) {
		Plane plane = cube.planes[i];
		
		if( Collision::spherePlane(start, radius, plane.normal, plane.verticles[0], plane.verticles[1], plane.verticles[2], plane.verticles[3]) )
			hasCollision = true;
	}
	
	return hasCollision;
}

//bool Collision::boxCube(vector3f& start, vector3f mins, vector3f maxs, Cube cube) {
//	float radius = Cube::SIZE/2;