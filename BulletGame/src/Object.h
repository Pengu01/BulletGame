#pragma once
#include "SDL.h"

class Object
{
public:
	//constructor to personalise the object
	Object(int width, int height, int velocity, SDL_Texture* objTexture);
	//event handler to get inputs
	void handleEvent(SDL_Event& e);
	//changing the x and y according to velocity
	void move();
	//puts it on the screen
	void render(SDL_Renderer* renderer);
	//rotate according to mouse position
	void rotate();
	//frees the texture
	void free();
private:
	int OBJ_WIDTH, OBJ_HEIGHT, OBJ_VEL;
	float mPosX, mPosY;
	float mVelX, mVelY;
	SDL_Texture* objTexture;
	SDL_Rect* clip = NULL;
	double angle = 0.0;
	SDL_Point* center = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
};