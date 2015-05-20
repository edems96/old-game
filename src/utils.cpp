#include "utils.h"

unsigned int Utils::loadTexture(const char* filename) {
	SDL_Surface *tmp = IMG_Load(filename);
	
	if( tmp == NULL ) {
		printf("Error! Cannot load image: %s\n", filename);
		return 0;
	}
	
	SDL_PixelFormat form = {NULL, 32, 4, 
							0, 0, 0, 0, 
							8, 8, 8, 8,
							0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff,
							0, 55};
							
	SDL_Surface *image = SDL_ConvertSurface(tmp, &form, SDL_SWSURFACE);
	
	unsigned int id;
	glGenTextures(1, &id);
	
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, image->pixels);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	SDL_FreeSurface(tmp);
	SDL_FreeSurface(image);
	
	return id;
}