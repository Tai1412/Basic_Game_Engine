#include "playerObject.h"


playerObject::playerObject()
{
	//constructor
	frame = 0;
	positionX = 0;
	positionY = 300;
	valueX = 0;
	valueY = 0;
	frameWidth = 0;
	frameHeight = 0;
	moveStatus = -1;//dont know right or left yet
}


playerObject::~playerObject()
{
}

bool playerObject::loadImage(std::string path, SDL_Renderer* screen)
{
	bool reUse = Entity::loadImage(path, screen);
	if (reUse == true)
	{
		frameWidth = rect.w / 8;
		frameHeight = rect.h;
	}
	return reUse;
}
void playerObject::setClip()
{
	if (frameWidth > 0 & frameHeight > 0)
	{
		clipFrame[0].x = 0;
		clipFrame[0].y = 0;
		clipFrame[0].w = frameWidth;
		clipFrame[0].h = frameHeight;

		clipFrame[1].x = frameWidth;
		clipFrame[1].y = 0;
		clipFrame[1].w = frameWidth;
		clipFrame[1].h = frameHeight;

		clipFrame[2].x = frameWidth*2;
		clipFrame[2].y = 0;
		clipFrame[2].w = frameWidth;
		clipFrame[2].h = frameHeight;

		clipFrame[3].x = frameWidth * 3;
		clipFrame[3].y = 0;
		clipFrame[3].w = frameWidth;
		clipFrame[3].h = frameHeight;

		clipFrame[4].x = frameWidth * 4;
		clipFrame[4].y = 0;
		clipFrame[4].w = frameWidth;
		clipFrame[4].h = frameHeight;

		clipFrame[5].x = frameWidth * 5;
		clipFrame[5].y = 0;
		clipFrame[5].w = frameWidth;
		clipFrame[5].h = frameHeight;

		clipFrame[6].x = frameWidth * 6;
		clipFrame[6].y = 0;
		clipFrame[6].w = frameWidth;
		clipFrame[6].h = frameHeight;

		clipFrame[7].x = frameWidth * 7;
		clipFrame[7].y = 0;
		clipFrame[7].w = frameWidth;
		clipFrame[7].h = frameHeight;
	}
}
void playerObject::draw(SDL_Renderer* des)
{
	if (moveStatus == moveToLeft)
	{
		loadImage("assets//player//playerMoveLeft.png", des);
	}
	else
	{
		loadImage("assets//player//playerMoveRight.png", des);
	}
	if (typeInput.moveLeft == 1 || typeInput.moveRight == 1)
	{
		frame++;
	}
	else
	{
		frame = 0;//if standing
	}
	if (frame >= 8)
	{
		frame = 0;
	}
	rect.x = positionX;
	rect.y = positionY;
	SDL_Rect* thisClip = &clipFrame[frame];
	SDL_Rect rect_ =
	{
		rect.x,
		rect.y,
		frameWidth,
		frameHeight
	};
	SDL_RenderCopy(des, object, thisClip, &rect_);
}
//event proccesss
void playerObject::handleInputEvent(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			moveStatus = moveToRight;
			typeInput.moveRight = 1;
		}
		break;
		case SDLK_LEFT:
		{
			moveStatus = moveToLeft;
			typeInput.moveLeft = 1;
		}
		break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			typeInput.moveRight = 0;
		}
		break;
		case SDLK_LEFT:
		{
			typeInput.moveLeft = 0;
		}
		break;
		}
	}
}
