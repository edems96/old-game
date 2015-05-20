#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>

#include "cube.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <ctime>

#include "vector3f.h"
#include "terrain.h"
#include "player.h"
#include "utils.h"
#include "textures.h"

#define VERSION "0.1"
#define TITLE "Game V. 0.1" // << VERSION
#define LOG 0

#define FOG 0

class Game {
	public:
		static const int MAX_FPS = 60;
		static const int DEFAULT_WIDTH = 1024;
		static const int DEFAULT_HEIGHT = 768;
		static const bool DEFAULT_FULLSCREEN = false;
		
		Game();
		Game(const int width, const int height);
		Game(const int width, const int height, const bool fs);
		~Game();
		
		void Start();
		
	private:
		int width;
		int height;
		bool isFullscreen;
		
		bool isRunning;
		
		std::vector<Cube> cubes;
		Player* player;
		
		Textures textures;
		Terrain terrain;
		
		int fps;

		void Init(const int width, const int height, const bool fs);
		void HandleEvents(SDL_Event event);
		
		void Update();
		void Draw();	
		
		void InitFog();
};

#endif