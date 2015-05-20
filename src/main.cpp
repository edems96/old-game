#include "Game.h"

// disable stdio rederection
#ifdef main
#undef main
#endif

int main(int argc, char *argv[]) {
	Game app(1024, 768);
	app.Start();
	
	return 0;
}