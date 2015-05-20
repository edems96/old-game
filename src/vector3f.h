#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <stdio.h>
#include <string>
#include <sstream>

class vector3f {
	public:
		float x;
		float y;
		float z;
		
		vector3f();
		vector3f(float x, float y); // as pitch & roll
		vector3f(float x, float y, float z);
		vector3f(const vector3f& vector);

		float length();
		vector3f normalize();
		
		float dotProduct(const vector3f& vector);
		vector3f crossProduct(const vector3f& vector);
		
		void set(float x, float y, float z);
		void set(const vector3f& vector);
		
		vector3f operator+(const vector3f& vector);
		vector3f operator-(const vector3f& vector);
		vector3f operator*(float n);
		vector3f operator/(float n);
		
		vector3f operator+=(const vector3f& vector);
		vector3f operator-=(const vector3f& vector);
		vector3f operator*=(float n);
		vector3f operator/=(float n);
		
		bool operator==(const vector3f vector);
		bool operator!=(const vector3f vector);
		
		std::string toString(); 
		const char* toChars();
};

#endif