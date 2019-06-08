#include "enemyObject.h"


enemyObject::enemyObject()
{
    //constructor
    frameWidth = 0;
    frameHeight = 0;
    valueX = 0;
    valueY = 0;
    positionX = 0;;
    positionY = 0;
    standGround = 0;
    timeBack = 0;
    frame = 0;
}


enemyObject::~enemyObject()
{
}

bool enemyObject::loadImage(std::string path, SDL_Renderer* screen)
{
    bool reUse = Entity::loadImage(path, screen);
    if (reUse)
    {
        frameWidth = rect.w / 8;
        frameHeight = rect.h;
    }
    return reUse;
}
void enemyObject::setClip()
{
    if (frameWidth > 0 && frameHeight > 0)
    {
        clipFrame[0].x = 0;
        clipFrame[0].y = 0;
        clipFrame[0].w = frameWidth;
        clipFrame[0].h = frameHeight;

        clipFrame[1].x = frameWidth;
        clipFrame[1].y = 0;
        clipFrame[1].w = frameWidth;
        clipFrame[1].h = frameHeight;

        clipFrame[2].x = frameWidth * 2;
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
void enemyObject::draw(SDL_Renderer* des)
{
    if (timeBack == 0)
    {
        rect.x = positionX - mapX;
        rect.y = positionY - mapY;
        frame++;
        if (frame >= 8)
        {
            frame = 0;
        }
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
}
void enemyObject::calMoveEnemy(myMap& mapData)
{
    if (timeBack == 0)
    {
        valueX = 0;
        valueY += FALL_SPEED;//speed fall down of enemy to the tile
        if (valueY >= MAXIMUM_F_SPEED)
        {
            valueY = MAXIMUM_F_SPEED;
        }
        checkEnemy(mapData);
    }
    else if (timeBack > 0)
    {
        timeBack--;
        if (timeBack = 0)
        {
            valueX = 0;
            valueY = 0;
            if (positionX > 320)
            {
                positionX -= 320;
            }
            else
            {
                positionX = 0;
            }
            positionY = 0;
            timeBack = 0;
        }
    }
}
void enemyObject::checkEnemy(myMap& mapData)
{
    int x1, x2 = 0;
    int y1, y2 = 0;
    int minHeight = frameHeight < tileSize ? frameHeight : tileSize;
    x1 = (positionX + valueX) / tileSize;//get current tileMat
    x2 = (positionX + valueX + frameWidth - 1) / tileSize;
    y1 = (positionY) / tileSize;
    y2 = (positionY + minHeight - 1) / tileSize;
    //check move
    if (x1 >= 0 && x2 < maxMapX && y1 >= 0 && y2 < maxMapY)
    {
        if (valueX > 0)//player moving to right
        {
            int value1 = mapData.tile[y1][x2];
            int value2 = mapData.tile[y2][x2];
                if ((value1 != emptyTile&& value1 !=diamond) || (value2 != emptyTile && value2 !=diamond))
                {
                    positionX = tileSize * x2;
                    positionX -= frameWidth + 1;
                    valueX = 0;//continue move but cant
                }
        }
        else if (valueX < 0)
        {
            int value1 = mapData.tile[y1][x1];
            int value2 = mapData.tile[y2][x1];
            if ((value1 != emptyTile&& value1 != diamond) || (value2 != emptyTile && value2 != diamond))
            {
                    positionX = tileSize*(x1 + 1);
                    valueX = 0;
                }
        }
    }

    int minWidth = frameWidth < tileSize ? frameWidth : tileSize;
    x1 = (positionX) / tileSize;
    x2 = (positionX + minWidth) / tileSize;
    y1 = (positionY + valueY) / tileSize;
    y2 = (positionY + valueY + frameHeight - 1) / tileSize;
    if (x1 >= 0 && x2 < maxMapX && y1 >= 0 && y2 < maxMapY)
    {
        if (valueY > 0)
        {
            int value1 = mapData.tile[y2][x1];
            int value2 = mapData.tile[y2][x2];
           
            if ((value1 != emptyTile&& value1 != diamond) || (value2 != emptyTile && value2 != diamond))
            {
                    positionY = tileSize * y2;
                    positionY -= (frameHeight + 1);
                    valueY = 0;
                    standGround = true;
                }
        }
        else if (valueY < 0)
        {
            int value1 = mapData.tile[y1][x1];
            int value2 = mapData.tile[y1][x2];
            if ((value1 != emptyTile&& value1 != diamond) || (value2 != emptyTile && value2 != diamond))
            {
                    positionY = (y1 + 1)*tileSize;
                    valueY = 0;
                }
        }
    }
    positionX += valueX;
    positionY += valueY;
    if (positionX < 0)
    {
        positionX = 0;
    }
    else if (positionX + frameWidth > mapData.maxX)
    {
        positionX = mapData.maxX = frameWidth - 1;
    }

    if (positionY>mapData.maxY)
    {
        timeBack = 60;//delay 60;
    }
}