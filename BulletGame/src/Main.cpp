#include "SDL.h"

//MAIN
int main(int argc, char* args[])
{
	SDL sdl;
	if (!sdl.initiate()) return 0;
	if (!sdl.loadassets()) return 0;
	sdl.start();
	return 0;
}
