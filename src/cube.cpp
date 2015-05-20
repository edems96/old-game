#include "cube.h"

Cube::Cube() {
	origin = vector3f();
	Init();
}

Cube::Cube(const vector3f origin) {
	this->origin = origin;
	Init();
}

Cube::Cube(const vector3f origin, bool generate) {
	this->origin = origin;
	
	Init();
	
	if( generate )
		Generate();
}

float Cube::randomColor() {
	return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}

void Cube::Init() {
	id 				= 0;
	flag 			= FLAG_SOLID;
	translateVector = vector3f();
	color			= vector3f(0.0f, 0.95f, 0.0f);
	
	type 			= GL_QUADS;
}

void Cube::GenerateRenderBuffer(float *output) {
	vector3f color(1.0f, 0.0f, 0.0f);
	
	float array[3*2*planes.size()*4];
	int offset = 0;
	
	for(int i = 0; i < planes.size(); i++) {
		Plane plane = planes[i];
		
		for(int v = 0; v < 4; v++) {
			array[offset++] = plane.verticles[v].x;
			array[offset++] = plane.verticles[v].y;
			array[offset++] = plane.verticles[v].z;
			
			array[offset++] = color.x;
			array[offset++] = color.y;
			array[offset++] = color.z;
		}
	}
	
	output = array;
}

Cube Cube::Generate() {

	// front
	planes.push_back(Plane(
	vector3f(origin.x-SIZE/2, origin.y+SIZE/2, origin.z+SIZE/2), 
	vector3f(origin.x+SIZE/2, origin.y+SIZE/2, origin.z+SIZE/2), 
	vector3f(origin.x+SIZE/2, origin.y-SIZE/2, origin.z+SIZE/2), 
	vector3f(origin.x-SIZE/2, origin.y-SIZE/2, origin.z+SIZE/2)));
	
	// rear
	planes.push_back(Plane(
	vector3f(origin.x-SIZE/2, origin.y+SIZE/2, origin.z-SIZE/2), 
	vector3f(origin.x+SIZE/2, origin.y+SIZE/2, origin.z-SIZE/2), 
	vector3f(origin.x+SIZE/2, origin.y-SIZE/2, origin.z-SIZE/2), 
	vector3f(origin.x-SIZE/2, origin.y-SIZE/2, origin.z-SIZE/2)));
	
	// top
	planes.push_back(Plane(
	vector3f(origin.x-SIZE/2, origin.y+SIZE/2, origin.z+SIZE/2), 
	vector3f(origin.x+SIZE/2, origin.y+SIZE/2, origin.z+SIZE/2), 
	vector3f(origin.x+SIZE/2, origin.y+SIZE/2, origin.z-SIZE/2), 
	vector3f(origin.x-SIZE/2, origin.y+SIZE/2, origin.z-SIZE/2)));
	
	// bottom
	planes.push_back(Plane(
	vector3f(origin.x-SIZE/2, origin.y-SIZE/2, origin.z+SIZE/2), 
	vector3f(origin.x+SIZE/2, origin.y-SIZE/2, origin.z+SIZE/2), 
	vector3f(origin.x+SIZE/2, origin.y-SIZE/2, origin.z-SIZE/2), 
	vector3f(origin.x-SIZE/2, origin.y-SIZE/2, origin.z-SIZE/2)));
	
	// left
	planes.push_back(Plane(
	vector3f(origin.x-SIZE/2, origin.y+SIZE/2, origin.z+SIZE/2), 
	vector3f(origin.x-SIZE/2, origin.y+SIZE/2, origin.z-SIZE/2), 
	vector3f(origin.x-SIZE/2, origin.y-SIZE/2, origin.z-SIZE/2), 
	vector3f(origin.x-SIZE/2, origin.y-SIZE/2, origin.z+SIZE/2)));
	
	// rights
	planes.push_back(Plane(
	vector3f(origin.x+SIZE/2, origin.y+SIZE/2, origin.z+SIZE/2), 
	vector3f(origin.x+SIZE/2, origin.y+SIZE/2, origin.z-SIZE/2), 
	vector3f(origin.x+SIZE/2, origin.y-SIZE/2, origin.z-SIZE/2), 
	vector3f(origin.x+SIZE/2, origin.y-SIZE/2, origin.z+SIZE/2)));
	
	/*float *buff;
	GenerateRenderBuffer(buff);
	unsigned int indarr[]={0,1,2};
	
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ind);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ind); // ELEMENT
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(buff), buff, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(indarr), indarr, GL_STATIC_DRAW);  */
		
	id = glGenLists(1);
	glNewList(id, GL_COMPILE);
	
		for(int i = 0; i < planes.size(); i++) {
			Plane plane = planes[i];
			
			glBindTexture(GL_TEXTURE_2D, texture);
			
			//glColor3f(color.x, color.y, color.z);
			//if( texture == 2 )
			//	glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
			glNormal3f(plane.normal.x, plane.normal.y, plane.normal.z);
			
			glBegin(type);
			for(int v = 0; v < 4; v++) {
				if( v == 0 )
					glTexCoord2f(0, 1);
				else if( v == 1 )
					glTexCoord2f(1, 1);
				else if( v == 2 )
					glTexCoord2f(1, 0);
				else
					glTexCoord2f(0, 0);
					
				glVertex3f(plane.verticles[v].x, plane.verticles[v].y, plane.verticles[v].z);
			}
			
			glEnd();	
		}
	
	glEndList();
	 
	return *this;
}

void Cube::Delete() {
	for(int i = 0; i < planes.size(); i++) 
		delete &planes[i];
		
	planes.clear();
	glDeleteLists(id, 1);
}

void Cube::Draw() {
	glTranslatef(translateVector.x, translateVector.y, translateVector.z);
	glCallList(id);
	
	/*glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ind);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, sizeof(float)*6, 0);
	glColorPointer(3, GL_FLOAT, sizeof(float)*6, (void*)(sizeof(float)*3));
	
	glDrawElements(GL_QUADS, 3, GL_UNSIGNED_INT, 0);
	
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); */
}

void Cube::setType(const int type) {
	this->type = type;
}

void Cube::Translate(vector3f newOrigin) {
	translateVector = (newOrigin - origin);
}

int Cube::getID() {
	return id;
}

void Cube::setColor(const vector3f color) {
	this->color = color;
}

Cube Cube::setTexture(const unsigned int texture) {
	this->texture = texture;
	
	return *this;
}