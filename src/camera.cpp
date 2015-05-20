#include "camera.h"

Camera::Camera() {
	init();
}

Camera::Camera(const vector3f& position) {
	this->position = position;
	init();
}

Camera::~Camera() {
}

void Camera::init() {
	pitch = 0.0f;
	yaw   = 0.0f;
	
	moveSpeed 	= 1.0f;
	mouseSpeed 	= 0.5f;
	
	mouseInside = false;
	
	const SDL_VideoInfo* info = SDL_GetVideoInfo();

	screenWidth 	= info->current_w;
	screenHeight 	= info->current_h;	
}

void Camera::lockCamera() {
	if( pitch > 90.0f )
		pitch = 90.0f;
	
	if( pitch < -90.0f )
		pitch = -90.0f;
		
	if( yaw > 0.0f )
		yaw += 360.0f;
		
	if( yaw > 360.0f )
		yaw -= 360.0f;
}

void Camera::moveCamera(const float &dir) {
	float radian = (yaw + dir) * M_PI/180.0f;
	
	position.x -= sin(radian) * moveSpeed;
	position.z -= cos(radian) * moveSpeed;
}

void Camera::moveCameraUp(const float &dir) {	
	float radian = (pitch + dir) * M_PI/180.0f;
	
	position.y += sin(radian) * moveSpeed;
}
		
void Camera::Control() {
	vector3f oldPosition(position);
	
	if( mouseInside ) {
		int midX = screenWidth / 2;
		int midY = screenWidth / 2;
		
		SDL_ShowCursor(SDL_DISABLE);
		
		int tmpx;
		int tmpy;
		
		SDL_GetMouseState(&tmpx,&tmpy);
		
		pitch 	+= mouseSpeed * (midY-tmpy);
		yaw		+= mouseSpeed * (midX-tmpx);
		
		lockCamera();
		
		SDL_WarpMouse(midX, midY);
		
		Uint8* state = SDL_GetKeyState(NULL);
	
		if( state[SDLK_w] ) {
			moveCamera(0.0f);
			//moveCameraUp(0.0f);
		} else if( state[SDLK_s] ) {
			moveCamera(180.f);
			//moveCameraUp(180.0f);
		}
		
		if( state[SDLK_a] )
			moveCamera(90.0f);
		else if( state[SDLK_d] )
			moveCamera(270.0f);
	}
	
	glRotatef(-pitch,	1.0f, 0.0f, 0.0f);
	glRotatef(-yaw,		0.0f, 1.0f, 0.0f);
	glTranslatef(-position.x, -position.y-8.0f, -position.z);
}

// getters & setters
vector3f Camera::getPosition() {
	return this->position;
}

void Camera::setPosition(vector3f vector) {
	this->position = vector;
}
		
float Camera::getPitch() {
	return pitch;
}

void Camera::setPitch(const float pitch) {
	this->pitch = pitch;
}
		
float Camera::getYaw() {
	return yaw;
}

void Camera::setYaw(const float yaw) {
	this->yaw = yaw;
}

float Camera::getMoveSpeed() {
	return moveSpeed;
}

void Camera::setMoveSpeed(const float speed) {
	moveSpeed = speed;
}
		
float Camera::getMouseSpeed() {
	return mouseSpeed;
}

void Camera::setMouseSpeed(const float speed) {
	mouseSpeed = speed;
}
		
bool Camera::isMouseInside() {
	return mouseInside;
}

void Camera::setMouseInside(const bool isMouseInside) {
	mouseInside = isMouseInside;
}

vector3f Camera::getVector() {
	return vector3f(
		-cos(pitch * M_PI/180.0) * sin(yaw * M_PI/180.0),
		 sin(pitch * M_PI/180.0),
		-cos(pitch * M_PI/180.0) * cos(yaw * M_PI/180.0));
}
