#ifndef UTILS_H
#define UTILS_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

// define GL_UNSIGNED_INT_8_8_8_8
#ifndef GL_UNSIGNED_INT_8_8_8_8
#define GL_UNSIGNED_INT_8_8_8_8 0x8035
#endif

class Utils {
	public:
		static unsigned int loadTexture(const char* filename);

};

#endif