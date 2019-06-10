#pragma once

#ifndef ENEMY_OBJECT_H_
#define ENEMY_OBJECT_H_
#define FALL_SPEED 1
#define MAXIMUM_F_SPEED 10
#include "parentFunction.h"
#include "Entity.h"
#include "playerBulletObject.h"
class enemyObject : public Entity
{
public:
    enemyObject();
    ~enemyObject();
    enum enemyMoveType
    {
        notMoveEnemy = 0,
        moveInLimitArea=1, //enemy move in specific area
    };
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
    void setEnemyMoveType(const int& moveType)
    {
        enemyMoveType = moveType;
    }
    void setAnimationMovePosition(const int& positionLeft, const int& positionRight)
    {
        animationLeft = positionLeft,
        animationRight = positionRight;
    }
    void setLeftInput(const int& inputLeft)
    {
        typeInput.moveLeft = inputLeft;
    }
    void processEnemyMoveType(SDL_Renderer *screen);
    std::vector<playerBulletObject*>getBullets()
        const
    {
        return bullets;
    }
    void setBullets(std::vector<playerBulletObject*> lBullets)
    {
        bullets = lBullets;
    }
    void figureBullets(playerBulletObject* bullet, SDL_Renderer* screen);
    void createBullets(SDL_Renderer* screen, const int& limitX, const int& limitY);
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
    int enemyMoveType;
    int animationLeft;
    int animationRight;
    myInput typeInput;
    std::vector<playerBulletObject*>bullets;

};

#endif

