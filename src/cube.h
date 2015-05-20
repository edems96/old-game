#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>

//#include <GL/gl.h>
//#include <GL/glu.h>

#include <vector>
#include <cstdlib>

#include "vector3f.h"
#include "plane.h"
#include "utils.h"


class Cube {
	vector3f origin;
	vector3f translateVector;
	
	vector3f color;
	
	unsigned int id;
	unsigned int type;
	unsigned int flag;
	unsigned int texture;
	
	unsigned int vbo;
	unsigned int ind;
	
	float renderBuffer[];
	void GenerateRenderBuffer(float array[]);
	
	public:
		std::vector<Plane> planes;
		
		static const float SIZE = 8.0f;
		
		static const int FLAG_SOLID = 0;
		static const int FLAG_NOT_SOLID = 1;
		
		Cube();
		Cube(const vector3f origin);
		Cube(const vector3f origin, bool generate);
		
		float randomColor();
		int getID();
		
		void Init();
		
		Cube Generate();
		void Draw();
		void Delete();
		
		void setType(const int type);
		void Translate(vector3f newOrigin);
		void setColor(const vector3f color);
		
		Cube setTexture(const unsigned int texture);
};

#endif