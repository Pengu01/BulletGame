#include "Object.h"

Object::Object(int width, int height, int velocity, SDL_Texture* texture, int scrHeight, int scrWidth)
{
	//sets variables for the object
	SCREEN_HEIGHT = scrHeight;
	SCREEN_WIDTH = scrWidth;
	OBJ_WIDTH = width;
	OBJ_HEIGHT = height;
	OBJ_VEL = velocity;
	mPosX = 0;
	mPosY = 0;
	mVelX = 0;
	mVelY = 0;
	objTexture = texture;
}

void Object::handleEvent(SDL_Event& e)
{
	//gets the inouts and adjusts the speed accordingly
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY -= OBJ_VEL; break;
		case SDLK_DOWN: mVelY += OBJ_VEL; break;
		case SDLK_LEFT: mVelX -= OBJ_VEL; break;
		case SDLK_RIGHT: mVelX += OBJ_VEL; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY += OBJ_VEL; break;
		case SDLK_DOWN: mVelY -= OBJ_VEL; break;
		case SDLK_LEFT: mVelX += OBJ_VEL; break;
		case SDLK_RIGHT: mVelX -= OBJ_VEL; break;
		}
	}
}

void Object::move()
{
	float diagonal = 1.0f;
	if(mVelX*mVelY != 0) diagonal = 0.7071f;
	mPosX += mVelX * diagonal;
	//If the object went too far to the left or right
	if ((mPosX < 0) || (mPosX + OBJ_WIDTH > SCREEN_WIDTH))
	{
		//Move back
		mPosX -= mVelX * diagonal;
	}
	mPosY += mVelY * diagonal;
	//If the object went too far up or down
	if ((mPosY < 0) || (mPosY + OBJ_HEIGHT > SCREEN_HEIGHT))
	{
		//Move back
		mPosY -= mVelY * diagonal;
	}
	return;
}

void Object::render(SDL_Renderer* renderer)
{
	SDL_Rect renderQuad = { mPosX, mPosY, OBJ_WIDTH, OBJ_HEIGHT };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, objTexture, clip, &renderQuad, angle, center, flip);
}

void Object::rotate()
{
	int x, y;
	//gets the mouse position
	SDL_GetMouseState(&x, &y);
	//gets the vector from the texture to the mouse
	float vecX = x-mPosX;
	float vecY = y-mPosY;
	//finds the angle for correct alignment
	angle = atan2(vecY, vecX) * 180 / M_PI+90;
}

void Object::free()
{
	SDL_DestroyTexture(objTexture);
}