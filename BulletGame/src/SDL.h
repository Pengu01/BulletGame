#pragma once
//SDL things
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include "Player.h"
#include <vector>

class SDL
{
public:
	//Game window size
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;
	//Game window
	SDL_Window* gWindow = NULL;
	//Surface of game window
	SDL_Surface* gScreenSurface = NULL;
	//Displayed game window surface
	SDL_Surface* gCurrentSurface = NULL;
	//Renderer
	SDL_Renderer* gRenderer = NULL;
	//start up SDL
	bool initiate();
	//Bullettexture
	SDL_Texture* gBulletTexture = NULL;
	//load textures
	bool loadassets();
	//gameloop
	void start();
	//Close and free
	void close();
	//loadtexture
	SDL_Texture* loadTexture(std::string path);
private:
	Uint64 gTime = 0;
};