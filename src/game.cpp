#include "game.h"

Game::Game() {
	Init(DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_FULLSCREEN);
}

Game::Game(const int width, const int height) {
	Init(width, height, DEFAULT_FULLSCREEN);
}

Game::Game(const int width, const int height, const bool fs) {
	Init(width, height, fs);
}

/*
	VBO-ba írni!
*/

void Game::Init(const int width, const int height, const bool fs) {
	this->width = width;
	this->height = height;
	this->isFullscreen = fs;
	this->isRunning = true;
	
	if( LOG ) {
		freopen("game.log", "w", stdout);
		freopen("game.error.log", "w", stderr);
	}
	
	srand(time(NULL));
	
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_WM_SetCaption(TITLE, NULL);
	
	SDL_Surface* screen;
	
	if( fs )
		screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE | SDL_OPENGL | SDL_FULLSCREEN);
	else
		screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE | SDL_OPENGL);
		
	if( screen == NULL ) {
		printf("Cannot start game!\n");
		this->isRunning = false;
		
		return;
	}
	
	/*if ( GLEW_OK != glewInit() ) {
    // GLEW failed!
    exit(1); // add some printf
	} */
	
	printf("Init(%d, %d, %d)\n", width, height, fs);
	
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)width / (float)height, 0.1f, 500.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	if( FOG )
		InitFog();
	
	textures.loadTextures();
	terrain.Generate(cubes, textures);
	
	/*for(int x = 0; x < 25; x++) {
		for(int y = 0; y < 25; y++) {
			cubes.push_back( Cube(vector3f(x * Cube::SIZE, 0, y * Cube::SIZE)).setTexture(textures.grass).Generate() );
		}
	}
	
	for(int i = 0; i < 25; i++) {
		if( rand() % 3 != 1 )
			continue;
			
		if( rand() % 2 == 0 )
			cubes.push_back( Cube(vector3f(i * Cube::SIZE, Cube::SIZE, 0.0f)).setTexture(textures.wall).Generate() );
		else
			cubes.push_back( Cube(vector3f(0.0f, Cube::SIZE, i * Cube::SIZE)).setTexture(textures.wall).Generate() );
	} */
	
	player = new Player(vector3f(10, 200, 10));
	
	printf("Initalized\n");
}

void Game::Start() {
	SDL_Event event;
	Uint32 startTime;
	
	//startTime = SDL_GetTicks();
	while( this->isRunning ) {
		startTime = SDL_GetTicks();

		HandleEvents(event);
		
		Update();
		Draw();
		
		SDL_GL_SwapBuffers();
		
		if( 1000.0f/MAX_FPS > (SDL_GetTicks()-startTime) )
			SDL_Delay(1000.0f/MAX_FPS - (SDL_GetTicks()-startTime));
		
		/*if (SDL_GetTicks() - startTime > 1000) {
			printf("fps: %d\n", fps);
			fps = 0;
			startTime += 1000; 
		}

		fps++; */
	}
}

void Game::HandleEvents(SDL_Event event) {
	while( SDL_PollEvent(&event) ) {
		switch( event.type ) {
			
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_F1: this->isRunning = false; break;
					case SDLK_ESCAPE: SDL_ShowCursor(SDL_ENABLE); player->getCamera()->setMouseInside(false); break;
					
					case SDLK_SPACE: player->Jump(); break;
					case SDLK_LSHIFT: player->setRunning(true); break;
					
				}
				break;
				
			case SDL_MOUSEBUTTONDOWN:
				if( !player->getCamera()->isMouseInside() )
					player->getCamera()->setMouseInside(true);
				
				break;
				
			case SDL_MOUSEBUTTONUP:
				if( !player->getCamera()->isMouseInside() )
					player->getCamera()->setMouseInside(true);
				else {
					switch(event.button.button) {
						case SDL_BUTTON_LEFT: player->CreateCube(cubes, textures.wall); break;

					}
				}
				break;
			
			case SDL_QUIT: this->isRunning = false; break;
				
			default:
			//	printf("Event type: %d\n", event.type);
				break;		
		}
	}
}

void Game::Update() {
	player->Update(cubes);
}

void Game::Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	player->getCamera()->Control();
	player->Draw();
	
	for(int i = 0; i < cubes.size(); i++) {
		cubes[i].Draw();
	}
	
	player->DrawCubeMesh();
}

void Game::InitFog() {
	glEnable(GL_FOG);
	
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 100.0f);
    glFogf(GL_FOG_END, 500.0f);
//  glFogi(GL_FOG_MODE, GL_EXP2);
//  glFogf(GL_FOG_DENSITY, .3);

    float color[] = {.5,.5,.5,1.};
    glFogfv(GL_FOG_COLOR, color);
}

Game::~Game() {
	SDL_Quit();
	printf("Shutdown...\n");
}