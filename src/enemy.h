#ifndef ENEMY_H
#define ENEMY_H

struct enemy {
	int id;
	std::vector<unsigned int> frames;
	// origin;
	int currentFrame;
	vector3f position;
	vector3f rotation;
	vector3f lookDirection;
	int health;
	//weapon* currentWeapon;

};

#endif