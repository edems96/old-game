#ifndef PLAYER_H
#define PLAYER_H

#include <cstring>
#include <vector>
#include <cmath>

#include "cube.h"
#include "vector3f.h"
#include "camera.h"
#include "collision.h"

#define DEFAULT_NAME "Unknown Solider"

class Player {
	std::string name;
	
	vector3f origin;
	vector3f angles;
	
	vector3f force;
	vector3f direction;
	
	float health;
	float energy;
	
	bool onGround;
	bool running;
	
	Camera camera;
	Collision collision;
	Cube cubeMesh;
	
	void Init();
	
	void UpdatePosition(const vector3f vector);
	void UpdateAngles();
	
	public:
		static const float RADIUS = 3.0f;
		static const float HEIGHT = 10.0f;
		
		static const float MAX_HEALTH = 100.0f;
		static const float DEFAULT_ENERGY = 10.0f;
		
		static const float SPEED = 1.0f;
		static const float SPEED_RUNNING = 2.2f;
		static const float SPEED_MOUSE = 0.4f;
		
		static const float JUMP_HEIGHT = 2.0f;
		
		Player();
		Player(const vector3f origin);
		Player(const vector3f origin, const vector3f angles);
		
		void Update(std::vector<Cube>& cubes);
		void Draw();
		
		void Jump();
		void setRunning(bool isR);
		
		// setters & getters
		std::string getName();
		void   setName(std::string name);
		
		vector3f getOrigin();
		void     setOrigin(vector3f origin);
		
		vector3f getAngles();
		void     setAngles(vector3f angles);
		
		float getHealth();
		void  setHealth(float health);	
		
		bool isOnGround();
		bool isRunning();
		
		Camera* getCamera();
		
		vector3f findCubeMeshPosition() ;
		void DrawCubeMesh();
		void CreateCube(std::vector<Cube>& cubes, unsigned int texture);
};


#endif