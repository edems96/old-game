#ifndef TEXTURES_H
#define TEXTURES_H

#include "utils.h"


class Textures {
	
	public:
		unsigned int sand;
		unsigned int dirt;
		unsigned int grass;
		unsigned int wall;
		unsigned int water;
		
		void loadTextures();
};

#endif