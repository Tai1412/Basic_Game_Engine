#pragma once
#ifndef PLAYER_OBJECT_H_
#define PLAYER_OBJECT_H_
#include "parentFunction.h"
#include "Entity.h"
class playerObject:
	public Entity
{
public:
	playerObject();
	~playerObject();

	bool loadImage(std::string path, SDL_Renderer* screen);
	void draw(SDL_Renderer* des);//will draw each frame
	void handleInputEvent(SDL_Event events, SDL_Renderer* screen);//handle event
	enum typeMove
	{
		moveToRight = 0,
		moveToLeft = 1
	};
	void setClip();

private:
	//declare variable
	float valueX;
	float valueY;
	float positionX;
	float positionY;
	int frameWidth;
	int frameHeight;
	SDL_Rect clipFrame[8];
	myInput typeInput;
	int frame;
	int moveStatus;

};

#endif

