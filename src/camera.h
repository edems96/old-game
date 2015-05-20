#ifndef CAMERA_H
#define CAMERA_H

#include "collision.h"

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <cmath>

#include "vector3f.h"


class Camera {
	private:
		vector3f position;
		
		int screenWidth;
		int screenHeight;
		
		float pitch;
		float yaw;
		
		float moveSpeed;
		float mouseSpeed;
		
		bool mouseInside;
		
		void init();
		void lockCamera();
		void moveCamera(const float &dir);
		void moveCameraUp(const float &dir);
		
		Collision collision;
	
	public:
		Camera();
		Camera(const vector3f& position);
		~Camera();
		
		void Control();
		
		// setters & getters
		vector3f getPosition();
		void 	 setPosition(vector3f vector);
		
		float getPitch();
		void  setPitch(const float pitch);
		
		float getYaw();
		void  setYaw(const float yaw);
		
		float getMoveSpeed();
		void  setMoveSpeed(const float speed);
		
		float getMouseSpeed();
		void  setMouseSpeed(const float speed);
		
		bool isMouseInside();
		void setMouseInside(const bool isMouseInside);

		vector3f getVector();
};

#endif