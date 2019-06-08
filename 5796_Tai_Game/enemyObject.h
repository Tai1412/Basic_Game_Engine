#pragma once

#ifndef ENEMY_OBJECT_H_
#define ENEMY_OBJECT_H_
#define FALL_SPEED 1
#define MAXIMUM_F_SPEED 10
#include "parentFunction.h"
#include "Entity.h"
class enemyObject : public Entity
{
public:
    enemyObject();
    ~enemyObject();
    bool loadImage(std::string path, SDL_Renderer* screen);
    void setValueX(const float& valX)
    {
        valueX = valX;
    }
    void setValueY(const float& valY)
    {
        valueY = valY;
    }
    void setPositionX(const float& posX)
    {
        positionX = posX;
    }
    void setPositionY(const float& posY)
    {
        positionY = posY;
    }
    float getPositionX()
        const
    {
        return positionX;
    }
    float getPositionY()
        const
    {
        return positionY;
    }
    void setMyMapXY(const int x, const int y)
    {
        mapX = x;
        mapY = y;
    }
    void setClip();
    void draw(SDL_Renderer* des);//will draw each frame
    int getFrameWidth()
        const
    {
        return frameWidth;
    }
    int getHeightFrame()
        const
    {
        return frameHeight;
    }
    //calculate move of enemy
    void calMoveEnemy(myMap& mapData);
    //check enemy stand on tile
    void checkEnemy(myMap& mapData);
private:
    //like playerobject
    int frame;
    int frameWidth;
    int frameHeight;
    SDL_Rect clipFrame[8];//frame 8
    bool standGround;
    int timeBack;
    float positionX;
    float positionY;
    float valueX;
    float valueY;
    int mapX;
    int mapY;

};

#endif

