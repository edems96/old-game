#include "textures.h"

void Textures::loadTextures() {
	sand	= Utils::loadTexture("resource/sand1.png");
	dirt 	= Utils::loadTexture("resource/dirt1.png");
	grass 	= Utils::loadTexture("resource/grass1.png");
	wall  	= Utils::loadTexture("resource/wall1.png"); // stone
	water   = Utils::loadTexture("resource/water1.png");
}