#include "playerBulletObject.h"


playerBulletObject::playerBulletObject()
{
    //constructor
    valueX = 0;
    valueY = 0;
    isFly = false;
}


playerBulletObject::~playerBulletObject()
{
}
void playerBulletObject::loadBulletShapeImage(SDL_Renderer* bulletImage)
{
    if (bulletShape == enemyBullet)
    {
        loadImage("assets//enemy//enemy_level_2_bullet.png", bulletImage);
    }

}
void playerBulletObject::handleBulletFly(const int& boundaryX, const int& boundaryY)
{
    if (bulletDirector == bulletDirectRight)
    {
        rect.x += valueX;
        if (rect.x > boundaryX)//exceed screen width
        {
            isFly = false;
        }
    }
    else if (bulletDirector == bulletDirectLeft)
    {
        rect.x -= valueX;
        if (rect.x < 0)
        {
            isFly = false;
        }
    }
    
}

