#include "SDL.h"

bool SDL::initiate()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf(SDL_GetError());
		return false;
	}
	gWindow = SDL_CreateWindow("BulletGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		printf(SDL_GetError());
		return false;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL)
	{
		printf(SDL_GetError());
		return false;
	}
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	printf("Time: %d\n", (SDL_GetTicks64() - gTime));
	return true;
}

bool SDL::loadassets()
{
	return true;
}

void SDL::start()
{
	SDL_Event e;
	bool quit = false;
	Player player(20,20,1,loadTexture("src/dot.bmp"));
	gBulletTexture = loadTexture("src/bullet.bmp");
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			player.handleEvent(e);
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		//updatetime
		gTime = SDL_GetTicks64();
		//Move the dot
		player.move();
		//rotate towards mouse
		player.rotate();
		//Clear screen
		SDL_RenderClear(gRenderer);
		//Render objects
		player.render(gRenderer);
		//Update screen
		SDL_RenderPresent(gRenderer);
	}
	player.free();
	close();
}

void SDL::close()
{
	SDL_DestroyTexture(gBulletTexture);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

SDL_Texture* SDL::loadTexture(std::string path)
{
	//texture to return
	SDL_Texture* newTexture = NULL;
	//Load image to texture
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		IMG_GetError();
		return newTexture;
	}
	//Create texture from loaded surface
	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	if (newTexture == NULL)
	{
		printf(SDL_GetError());
		return newTexture;
	}
	//free the old surface
	SDL_FreeSurface(loadedSurface);
	return newTexture;
}
