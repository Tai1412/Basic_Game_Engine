#include "parentFunction.h"
#include "Entity.h"
#include "map.h"
#include "playerObject.h"
#include "enemyObject.h"
#include "timerFps.h"
#include <iostream>

Entity myBackground;
Map myGameMap;
playerObject player;
timerFps fps;
bool initData()
{
	bool success = true;
	int init = SDL_Init(SDL_INIT_EVERYTHING);
	if (init < 0)
	{
		cout << "SDL Fail initialised!!!\n";
		return false; //failed, dont continue rest of main code
	}
	else
	{
		cout << "SDL initialised success!!!\n";
	}
	//quality mode set
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	//create window, params are: window title, window pos x, pos y, width, height, window flags
	window = SDL_CreateWindow("5796_Tai_Game_ShootMonster", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);/*| SDL_WINDOW_FULLSCREEN*/
	if (window == NULL){
		success = false;
		cout << "Failed to create window!" << endl;
	}
	else
	{
		screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (screen == NULL)
		{
			success = false;
			cout << "Renderer FAILED!" << endl;
		}
		else
		{
			//set rendere color
			SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);
			int imageFlag = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlag) && imageFlag))
				success = false;
		}
		cout << "Succes create window" << endl;
	}
	return success;
}
void close()
{
	myBackground.free();

	SDL_DestroyRenderer(screen);
	screen = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}
std::vector<enemyObject*> enemies()
{
    std::vector<enemyObject*> enemiesList;
    enemyObject* moveEnemy = new enemyObject[25];//25
    for (int i = 0; i < 25; i++)
    {
        enemyObject* enemy = (moveEnemy + i);
        if (enemy != NULL)
        {
            enemy->loadImage("assets//enemy//enemy_level_1_left.png", screen);
            enemy->setClip();
            enemy->setEnemyMoveType(enemyObject::moveInLimitArea);
            enemy->setPositionX(500 + i * 400);
            enemy->setPositionY(200);//fall down from postion y =200
            int position1 = enemy->getPositionX() - 60;//depend on currently positionX
            int position2 = enemy->getPositionX() + 60;
            enemy->setAnimationMovePosition(position1, position2);
            enemy->setLeftInput(1);//not move
            enemiesList.push_back(enemy);
        }
    }
    enemyObject* eneObject = new enemyObject[25];//25 enemies random on map, for enemyNotMove
    for (int i = 0; i < 25; i++)
    {
        enemyObject* enemy = (eneObject + i);
        if (enemy != NULL)
        {
            enemy->loadImage("assets//enemy//enemy_level_2.png", screen);
            enemy->setClip();
            enemy->setPositionX(700 + i *500);//position their standing on ground on map
            enemy->setPositionY(200);//fall down from postion y =200
            enemy->setEnemyMoveType(enemyObject::notMoveEnemy);
            enemy->setLeftInput(0);//not move
            //shoot bullet
            playerBulletObject* bullet = new playerBulletObject();
            enemy->figureBullets(bullet, screen);
            enemiesList.push_back(enemy);
        }
    }
    return enemiesList;
}

bool loadBackgroundImage()
{
	//load image to screen
	bool img = myBackground.loadImage("assets//background//myBackground.png",screen);
	if (img == false)
	{
		cout << "failed load background";
		return false;
	}
	else{
		cout << "success to load background" << endl;
	}
	return true;
}

int main(int argc, char **argv)
{
	bool isQuit = false;
	if (initData() == false)
	{
		return -1;
	}

	if (loadBackgroundImage()==false)
	{
		return -1;
	}

	myGameMap.loadMyMap("assets/myMap/myMapSet.dat");
	myGameMap.loadMyMapTiles(screen);

	player.loadImage("assets//player//playerMoveRight.png", screen);//load image
	player.setClip();

    std::vector<enemyObject*> listEnemies = enemies();

	while (!isQuit)
	{
		fps.startRun();
		while (SDL_PollEvent(&_event) != 0)
		{
			if (_event.type == SDL_QUIT)
			{
				isQuit = true;
			}
			player.handleInputEvent(_event, screen);
		}
		SDL_SetRenderDrawColor(screen, 167, 167, 167, 167);
		SDL_RenderClear(screen);
		myBackground.render(screen, NULL);
		//myGameMap.drawMyMap(screen);//render map to screen
		myMap mapData = myGameMap.getMyMap();
        player.proccessBulletShoot(screen);
		player.setMyMapXY(mapData.startX, mapData.startY);
		player.calMovePlayer(mapData);
		player.draw(screen);
		myGameMap.setMyMap(mapData);
		myGameMap.drawMyMap(screen);
        for (int i = 0; i < listEnemies.size(); i++)
        {
            enemyObject* enemy = listEnemies.at(i);
            if (enemy != NULL)
            {
                enemy->setMyMapXY(mapData.startX, mapData.startY);
                enemy->processEnemyMoveType(screen);
                enemy->calMoveEnemy(mapData);
                enemy->createBullets(screen, screenWidth, screenHeight);
                enemy->draw(screen);

                //check collise of monster to character
                SDL_Rect playerRect = player.getFrameRect();
                bool pCollision = false;
                std::vector<playerBulletObject*> bullets = enemy->getBullets();
                for (int j = 0; j < bullets.size(); ++j)
                {
                    playerBulletObject* eBullets = bullets.at(j);//enemy bullets
                    if (eBullets)
                    {
                        pCollision = parentFunction::entityColliseChecking(eBullets->getRect(), playerRect);//check enemy bullet on character
                        if (pCollision)
                        {
                            enemy->destroyBullet(j);
                            break;
                        }
                    }
                }
                SDL_Rect eneRect = enemy->getFrameRect();
                bool eCollision = parentFunction::entityColliseChecking(playerRect, eneRect);
                if (pCollision || eCollision)//if  1 of them true, character die
                {
                    //destroy end quit for now
                        enemy->free();
                        close();
                        SDL_Quit();
                        return 0;
                }

            }
        }
    std:vector<playerBulletObject*> bullets = player.getBullets();
        for (int t = 0; t < bullets.size(); ++t)
        {
            playerBulletObject* playerBullet = bullets.at(t);
            if (playerBullet != NULL)
            {
                //check each bullet for each enemy
                for (int b = 0; b < listEnemies.size();++b)
                { 
                    enemyObject* enemy = listEnemies.at(b);
                    if (enemy != NULL)
                    {
                        SDL_Rect bRect;
                        bRect.x = enemy->getRect().x;
                        bRect.y = enemy->getRect().y;
                        bRect.w = enemy->getFrameWidth();//take 1 frame
                        bRect.h = enemy->getHeightFrame();

                        SDL_Rect tRect = playerBullet->getRect();
                        //check collise or not
                        bool tCollisition = parentFunction::entityColliseChecking(tRect, bRect);
                        if (tCollisition)//true, destroy bullet
                        {
                            player.destroyBullet(t);
                            enemy->free();
                            listEnemies.erase(listEnemies.begin() + b);//remove the enemy
                        }
                    }
                }
            }
        }
		SDL_RenderPresent(screen);

		int realTime = fps.getTick();
		int timeForFrame = 1000 / framePerSecond;//1000ms time for one frame
		//the fps small, game will be slowly
		//the fps large, game will be faster
		if (realTime < timeForFrame)//latency
		{
			int delayTime = timeForFrame - realTime;
			if (delayTime>=0)
			{ 
				SDL_Delay(delayTime);
			}
			
		}
	}
    //free when game close
    for (int i = 0; i < listEnemies.size(); i++)
    {
        enemyObject* enemy = listEnemies.at(i);
        if (enemy != NULL)
        {
            enemy->free();
            enemy = NULL;
        }
    }
    listEnemies.clear();
	close();
	return 0;
}
