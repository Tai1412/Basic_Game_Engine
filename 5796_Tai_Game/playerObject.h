#pragma once
#ifndef PLAYER_OBJECT_H_
#define PLAYER_OBJECT_H_
#define FALL_SPEED 1
#define MAXIMUM_F_SPEED 10
#define CHARACTER_SPEED 8
#define CHARACTER_JUMMP 20
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

	//calculate move of player
	void calMovePlayer(myMap& mapData);
	//check character stand on tile
	void checkPlayer(myMap& mapData);
	//set Map
	void setMyMapXY(const int x, const int y)
	{
		mapX = x;
		mapY = y;
	}
	void entityOnMap(myMap& mapData);
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
	bool standGround;
	int moveStatus;
	int mapX;
	int mapY;
};

#endif

