#pragma once
#ifndef PLAYER_OBJECT_H_
#define PLAYER_OBJECT_H_
#define FALL_SPEED 1
#define MAXIMUM_F_SPEED 10
#define CHARACTER_SPEED 8
#define CHARACTER_JUMMP 20
#include "parentFunction.h"
#include "Entity.h"
#include "playerBulletObject.h"
#include <vector>//for bullet
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
        noneMove = 0,
		moveToRight = 1,
		moveToLeft = 2
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
    void updatePlayerImage(SDL_Renderer* des);
	void entityOnMap(myMap& mapData);
    void increaseDiamond();//for eat diamond func, increaseby 1
    void setBullets(std::vector<playerBulletObject*> lBullets)
    {
        bullets = lBullets;
    }
    std::vector<playerBulletObject*>getBullets()
        const
    {
        return bullets;
    }
    void proccessBulletShoot(SDL_Renderer* des);

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
	int timeBack;
	int mapX;
	int mapY;
    int diamondCount;
    std::vector<playerBulletObject*> bullets;
};

#endif

