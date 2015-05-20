#include "vector3f.h"

vector3f::vector3f() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

vector3f::vector3f(float x, float y) {
	this->x = x;
	this->y = y;
}

vector3f::vector3f(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

vector3f::vector3f(const vector3f& vector) {
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
}

float vector3f::length() {
	return sqrt(x*x + y*y + z*z);
}

vector3f vector3f::normalize() {
	float l = length();
	
	if( l == 0 )
		return *this;
		
	x /= l;
	y /= l;
	z /= l;
	
	return *this;
}

		
float vector3f::dotProduct(const vector3f& vector) {
	return (x * vector.x + y * vector.y + z * vector.z);
}

vector3f vector3f::crossProduct(const vector3f& vector) {
	return vector3f(y*vector.z - z*vector.y, x*vector.z - z*vector.x, x*vector.y - y*vector.x);
}
		
void vector3f::set(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void vector3f::set(const vector3f& vector) {
	x = vector.x;
	y = vector.y;
	z = vector.z;
}
	
vector3f vector3f::operator+(const vector3f& vector) {
	return vector3f(x + vector.x, y + vector.y, z + vector.z);
}

vector3f vector3f::operator-(const vector3f& vector) {
	return vector3f(x - vector.x, y - vector.y, z - vector.z);
}

vector3f vector3f::operator*(float n) {
	return vector3f(x * n, y * n, z * n);
}

vector3f vector3f::operator/(float n) {
	if( n == 0 ) {
		printf("You trying to divide by ZERO!\n");
		return vector3f(*this);
	}
	
	return vector3f(x / n, y / n, z / n);
}
			
vector3f vector3f::operator+=(const vector3f& vector) {
	x += vector.x;
	y += vector.y;
	z += vector.z;
	
	return *this;
}

vector3f vector3f::operator-=(const vector3f& vector) {
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	
	return *this;
}

vector3f vector3f::operator*=(float n) {
	x *= n;
	y *= n;
	z *= n;
	
	return *this;
}

vector3f vector3f::operator/=(float n) {
	if( n == 0 ) {
		printf("You trying to divide by ZERO!\n");
		return *this;
	}
		
	x /= n;
	y /= n;
	z /= n;
	
	return *this;
}
		
bool vector3f::operator==(const vector3f vector) {
	return ( x == vector.x && y == vector.y && z == vector.z );
}

bool vector3f::operator!=(const vector3f vector) {
	return !(*this == vector);
}
		
std::string toStr (float number) {
	std::ostringstream buff;
	buff << number;
	
    return buff.str();
}

std::string vector3f::toString() {
	std::string ret;
	ret += "(";
	ret += toStr(x);
	ret += ", ";
	ret += toStr(y);
	ret += ", ";
	ret += toStr(z);
	ret += ")";
	
	return ret;
}

const char* vector3f::toChars() {
	return toString().c_str();
}