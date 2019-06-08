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
	moveStatus = noneMove;//set initial noneMove
	typeInput.moveLeft = 0;
	typeInput.moveRight = 0;
	typeInput.jump = 0;
	standGround = false;
	timeBack = 0;
	mapX = 0;
	mapY = 0;
    diamondCount = 0;
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
    updatePlayerImage(des);
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
	if (timeBack == 0)
	{
		rect.x = positionX - mapX;
		rect.y = positionY - mapY;
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
			typeInput.moveLeft = 0;
            updatePlayerImage(screen);
		}
		break;
		case SDLK_LEFT:
		{
			moveStatus = moveToLeft;
			typeInput.moveLeft = 1;
			typeInput.moveRight = 0;
            updatePlayerImage(screen);
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
	//jump for character
	if (events.type == SDL_MOUSEBUTTONDOWN)//mouse button press
	{
		if (events.button.button == SDL_BUTTON_RIGHT)//click right mouse to jump
		{
			typeInput.jump = 1;
		}
        else if (events.button.button == SDL_BUTTON_LEFT)//for shoot bullet
        {
            playerBulletObject* bullet = new playerBulletObject();
            if (moveStatus == moveToLeft)
            {
                bullet->setBulletDirector(playerBulletObject::bulletDirectLeft);
                bullet->setRect(this->rect.x, rect.y + frameHeight*0.3);
                bullet->loadImage("assets//player//bulletLeft.png", screen);//load bullet left image
            }
            else
            {
                bullet->setBulletDirector(playerBulletObject::bulletDirectRight);
                bullet->setRect(this->rect.x + frameWidth - 25, rect.y + frameHeight*0.3);
                bullet->loadImage("assets//player//bulletRight.png", screen);//load bullet right image
            }
            bullet->setValueX(20);//speed ofbullet
            bullet->setIsFly(true);
            bullets.push_back(bullet);//shoot
        }
	}
}
void playerObject::proccessBulletShoot(SDL_Renderer* des)
{
    for (int i = 0; i < bullets.size(); i++)//check whehter bullets have or not
    {
        playerBulletObject* bullet = bullets.at(i);
        if (bullet != NULL)
        {
            if (bullet->getIsFly() == true)
            {
                bullet->handleBulletFly(screenWidth, screenHeight);
                bullet->render(des);
            }
            else
            {
                //delete if it exceed boundary
                bullets.erase(bullets.begin() + i);
                if (bullet != NULL)//check
                {
                    delete bullet;
                    bullet = NULL;
                }
                
            }
        }
    }
}
void playerObject::calMovePlayer(myMap& mapData)
{
    //when the time back == 0 , character respawn
	if (timeBack == 0)
	{
		valueX = 0;
		valueY += 1;//speed fall down of character to the tile
		if (valueY >= MAXIMUM_F_SPEED)
		{
			valueY = MAXIMUM_F_SPEED;
		}
		if (typeInput.moveLeft == 1)
		{
			valueX -= CHARACTER_SPEED; //move left x
		}
		else if (typeInput.moveRight == 1)
		{
			valueX += CHARACTER_SPEED;
		}
		if (typeInput.jump == 1)
		{
			if (standGround == true)
			{
				valueY = -CHARACTER_JUMMP;//in case of character on ground , they can jump, otherwise they can't
			}
			typeInput.jump = 0;
			standGround = false;
		}
		checkPlayer(mapData);
		entityOnMap(mapData);//entity on the map center
	}

     //check time back>0 ,minus iit until ==0 and minus position of character standing on the ground
	if (timeBack > 0)
	{
		timeBack--;
		if (timeBack == 0)//reset 
		{
            standGround = false;
			if (positionX > 320)//5 tile matt, 1 tilematt =64px
			{
				positionX -= 320;
			}
			else{
				positionX = 0;
			}

			positionY = 0;
			valueX = 0;
			valueY = 0;
		}
	}
	
	
}
void playerObject::entityOnMap(myMap& mapData)
{
	mapData.startX = positionX - (screenWidth / 2);
	if (mapData.startX < 0)
	{
		mapData.startX = 0;
	}
	else if (mapData.startX + screenWidth >= mapData.maxX)
	{
		mapData.startX = mapData.maxX - screenWidth;
	}
	mapData.startY = positionY - (screenHeight / 2);
	if (mapData.startY < 0)
	{
		mapData.startY = 0;
	}
	else if (mapData.startY + screenHeight >= mapData.maxY)
	{
		mapData.startY = mapData.maxY - screenHeight;
	}
}
void playerObject::updatePlayerImage(SDL_Renderer* des)
{
    if (standGround == true)
    {
        if (moveStatus == moveToLeft)
        {
            loadImage("assets//player//playerMoveLeft.png", des);
        }
        else
        {
            loadImage("assets//player//playerMoveRight.png", des);
        }
    }
    else{
        if (moveStatus == moveToLeft)
        {
            loadImage("assets//player//playerJumpLeft.png",des);
        }
        else
        {
            loadImage("assets//player//playerJumpRight.png", des);
        }
    }
}
void playerObject::increaseDiamond()
{
    diamondCount++;
}
void playerObject::checkPlayer(myMap& mapData)
{
	int x1,x2 = 0;
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
            if (value1 == diamond || value2 == diamond)//touch diamon, diamond tilemat disapear
            {
                mapData.tile[y1][x2] = 0;
                mapData.tile[y2][x2] = 0;
                increaseDiamond();
            }
            else
            {
                if (value1 != emptyTile || value2 != emptyTile)
                {
                    positionX = tileSize * x2;
                    positionX -= frameWidth + 1;
                    valueX = 0;//continue move but cant
                }
            }
		}
        else if (valueX < 0)
        {
            int value1 = mapData.tile[y1][x1];
            int value2 = mapData.tile[y2][x1];
            if (value1 == diamond || value2 == diamond)//touch diamon, diamond tilemat disapear
            {
                mapData.tile[y1][x1] = 0;
                mapData.tile[y2][x1] = 0;
                increaseDiamond();
            }
            else
            {
                if (value1 != emptyTile || value2 != emptyTile)
                {
                    positionX = tileSize*(x1 + 1);
                    valueX = 0;
                }
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
            if (value1 == diamond || value2 == diamond)
            {
                mapData.tile[y2][x1] = 0;
                mapData.tile[y2][x2] = 0;
                increaseDiamond();
            }
            else
            {
                if (value1 != emptyTile || value2 != emptyTile)
                {
                    positionY = tileSize * y2;
                    positionY -= (frameHeight + 1);
                    valueY = 0;
                    standGround = true;
                    if (moveStatus == noneMove)
                    {
                        moveStatus = moveToRight;
                    }
                }
            }
		}
		else if (valueY < 0)
		{
            int value1 = mapData.tile[y1][x1];
            int value2 = mapData.tile[y1][x2];
            if (value1 == diamond || value2 == diamond)
            {
                mapData.tile[y1][x1] = 0;
                mapData.tile[y1][x2] = 0;
                increaseDiamond();
            }
            else
            {
                if (value1 != emptyTile || value2 != emptyTile)
                {
                    positionY = (y1 + 1)*tileSize;
                    valueY = 0;
                }
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