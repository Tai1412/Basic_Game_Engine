#pragma once
#include "Entity.h"
#include "parentFunction.h"
#ifndef PLAYER_BULLET_OBJECT_H_
#define PLAYER_BULLET_OBJECT_H_
class playerBulletObject:public Entity
{
public:
    playerBulletObject();
    ~playerBulletObject();
    enum playerBulletDirector
    {
        bulletDirectRight=10,
        bulletDirectLeft=11
    };
    void setValueX(const int& x)
    {
        valueX = x;
    }
    void setValueY(const int& y)
    {
        valueY = y;
    }
    int getValueX()
        const
    {
        return valueX;
    }
    int getValueY()
        const
    {
        return valueY;
    }
    void setIsFly(const bool& is_Fly)//set
    {
        isFly = is_Fly;
    }
    bool getIsFly()//get
        const
    {
        return isFly;
    }
    void setBulletDirector(const int& bulletDirect)//set bullet Direction
    {
        bulletDirector = bulletDirect;
    }
    int getBulletDirector()//get bullet Direction
        const
    {
        return bulletDirector;
    }
    void handleBulletFly(const int& boundaryX, const int& boundaryY);//limit screen x,y axis for checkig bullet
   
private:
    int valueX;
    int valueY;
    int bulletDirector;
    bool isFly;
};

#endif

