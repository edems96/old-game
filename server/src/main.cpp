#include <SDL/SDL.h>
#include <SDL2/SDL_net.h>

#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>

// #define SDL_reinterpret_cast(type, expression) reinterpret_cast<type>(expression)

// disable stdio rederection
#ifdef main
#undef main
#endif

#define BUFFER_SIZE 1023

struct data {
	TCPsocket socket;
	Uint32 timeout;
	int id;
	
	data(TCPsocket c_socket, Uint32 c_timeout, int c_id) : socket(c_socket), timeout(c_timeout), id(c_id) {}
};

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();
	
	int currentID = 0;
	int countPlayers = 0;
	
	SDL_Event event;
	IPaddress ip;
	
	SDLNet_ResolveHost(&ip, NULL, 1234);
	
	std::vector<data> socketVector;
	
	char tmp[BUFFER_SIZE];
	bool running = true;
	

	SDLNet_SocketSet sockets = SDLNet_AllocSocketSet(30);
	SDL_SetVideoMode(1024, 768, 32, SDL_SWSURFACE);
	TCPsocket server = SDLNet_TCP_Open(&ip);
	
	while( running ) {
		while( SDL_PollEvent(&event) ) {
			if( event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE )
				running = false;
		}
		
		TCPsocket tmpSocket = SDLNet_TCP_Accept(server);
		
		if( tmpSocket ) {
			if( countPlayers < 30 ) {
				SDLNet_TCP_AddSocket(sockets, tmpSocket);
				socketVector.push_back( data(tmpSocket, SDL_GetTicks(), currentID) );
				countPlayers++;
				
				sprintf(tmp, "0 %d\n", currentID);
				printf("New connection: %d\n", currentID);
				
				currentID++;
			} else {
				sprintf(tmp, "3 \n");
			}
			
			SDLNet_TCP_Send(tmpSocket, tmp, strlen(tmp)+1);
		}
		
		// check for incoming data
		
		while( SDLNet_CheckSockets(sockets, 0) > 0 ) {
			for(int i = 0; i < socketVector.size(); i++) {
				
				if( SDLNet_SocketReady(socketVector[i].socket) ) {
					socketVector[i].timeout = SDL_GetTicks();
					SDLNet_TCP_Recv(socketVector[i].socket, tmp, BUFFER_SIZE);
					
					int num = tmp[0] - '0';
					int j = 1;
					
					while( tmp[j] >= '0' && tmp[j] <= '9' ) {
						num *= 10;
						num += tmp[j] - '0';
						j++;
					}

					if( num == 1 ) {
						for(int k = 0; k < socketVector.size(); k++) {
							if( k == i )	
								continue;
								
							SDLNet_TCP_Send(socketVector[k].socket, tmp, strlen(tmp)+1);
						}
					} else if( num == 2 ) {
						for(int k = 0; k < socketVector.size(); k++) {
							if( k == i )	
								continue;
								
							SDLNet_TCP_Send(socketVector[k].socket, tmp, strlen(tmp)+1);
						}
						
						SDLNet_TCP_DelSocket(sockets, socketVector[i].socket);
						SDLNet_TCP_Close(socketVector[i].socket);
						socketVector.erase(socketVector.begin()+i);
						countPlayers--;
					} else if( num == 3 ) {
						int tmpvar;
						
						sscanf(tmp, "3 %d", &tmpvar);
						for(int k = 0; k < socketVector.size(); k++) {
							if( socketVector[k].id == tmpvar ) {
								SDLNet_TCP_Send(socketVector[k].socket, tmp, strlen(tmp)+1);
								break;
							}
						}
					}
					
				}
				
			}
		}
		
		// timeout disconnect
		for(int j = 0; j < socketVector.size(); j++) {
			if( SDL_GetTicks() - socketVector[j].timeout > 5000 ) {
				sprintf(tmp, "2 %d \n", socketVector[j].id);
				
				for(int k = 0; k < socketVector.size(); k++) {
					SDLNet_TCP_Send(socketVector[k].socket, tmp, strlen(tmp)+1);
				}
						
				SDLNet_TCP_DelSocket(sockets, socketVector[j].socket);
				SDLNet_TCP_Close(socketVector[j].socket);
				socketVector.erase(socketVector.begin()+j);
				countPlayers--;
			}
		}
		
		SDL_Delay(1);
	}
	
	for(int i = 0; i < socketVector.size(); i++) {
		SDLNet_TCP_Close(socketVector[i].socket);
	}
	
	SDLNet_FreeSocketSet(sockets);
	SDLNet_TCP_Close(server);
	SDLNet_Quit();
	
	SDL_Quit();
}