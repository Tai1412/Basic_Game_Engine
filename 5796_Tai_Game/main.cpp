#include "parentFunction.h"
#include "Entity.h"
#include "map.h"
#include "playerObject.h"
#include "enemyObject.h"
#include "manageExploision.h"
#include "manageDisplayThing.h"
#include "timerFps.h"
#include <iostream>

Entity myBackground;
Map myGameMap;
playerObject player;
timerFps fps;
manageExploision enemyExploded;
manageExploision playerExploded;
TTF_Font* font=NULL;
TTF_Font* menuFont = NULL;

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
        if (TTF_Init() == -1)
        {
            success = false;
        }
        font = TTF_OpenFont("assets//font//vermin_vibes_1989.ttf",20);//size 12
        if (font == NULL)
        {
            success = false;
        }
        menuFont = TTF_OpenFont("assets//font//vermin_vibes_1989.ttf", 60);//size 60
        if (menuFont == NULL)
        {
            success = false;
        }
        //sound
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            return false;
        }
        playerBulletSound = Mix_LoadWAV(playerBullet);
        enemyExplodedSound = Mix_LoadWAV(enemyExplodedS);
        playerExplodedSound = Mix_LoadWAV(playerExplodedS);
        if (playerBulletSound == NULL || enemyExplodedSound == NULL || playerExplodedSound == NULL)
        {
            return false;
        }
        backGroundSound = Mix_LoadMUS(backGroundS);
        if (backGroundSound == NULL){
            return false;
        }
       
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
    //pause
    Mix_PausedMusic();
    //delete song from memory
    Mix_FreeMusic(backGroundSound);

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
    //		how many times to loop the music (-1 play infinitely)
    Mix_PlayMusic(backGroundSound, -1);

	myGameMap.loadMyMap("assets/myMap/myMapSet.dat");
	myGameMap.loadMyMapTiles(screen);

	player.loadImage("assets//player//playerMoveRight.png", screen);//load image
	player.setClip();

    diamondScore diamondScoreIcon;
    diamondScoreIcon.init(screen);
    diamondScoreIcon.setPosition(screenWidth*0.5 - 220, 0);

    std::vector<enemyObject*> listEnemies = enemies();

    bool expl = enemyExploded.loadImage("assets//exploi//exploi.png", screen);//loadimage exploi oof ene
    if (!expl)
    {
        return -1;
    }
    enemyExploded.setClip();
    expl = playerExploded.loadImage("assets//exploi//exploi.png", screen);//loadimage exploi of player
    if (!expl)
    {
        return -1;
    }
    playerExploded.setClip();
    //player life
    int deadTimes = 0;

    //game time count
    manageDisplayThing gameTimeCount;
    gameTimeCount.setColor(manageDisplayThing::textBlack);//black

    manageDisplayThing scoreCount;//kill monster score
    scoreCount.setColor(manageDisplayThing::textBlack);//black
    UINT scoreValue = 0;

    manageDisplayThing diamondGCount;//player take diamon score
    diamondGCount.setColor(manageDisplayThing::textBlack);//black

    manageDisplayThing playerLife;//life of character
    playerLife.setColor(manageDisplayThing::textRed);//red
    UINT playerLifeValue = 3;
    //menu
    int menu = parentFunction::menu(screen, menuFont);
    if (menu == 1)
    {
        MessageBox(NULL, L"You have 3 life, Just run and kill monster before times up \n Lets Play", L"Guide", MB_OK  | MB_RIGHT) == IDOK;
    }
    if (menu == 2)
    {
        isQuit = true;
    }
       
	while (!isQuit)
	{
		fps.startRun();
		while (SDL_PollEvent(&_event) != 0)
		{
			if (_event.type == SDL_QUIT)
			{
				isQuit = true;
			}
			player.handleInputEvent(_event, screen,playerBulletSound);
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
        diamondScoreIcon.draw(screen);
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
                    int frameExploiWidth = playerExploded.getFrameWidht();
                    int frameExploiHeight = playerExploded.getFrameHeight();
                    for (int i = 0; i < 8; i++)//collide exploid
                    {
                        //when the bullet touch, exploi in center
                        int positionX = (player.getRect().x + player.getFrameWidht()*0.5) - frameExploiWidth*0.5;
                        int positionY = (player.getRect().y + player.getFrameHeight()*0.5) - frameExploiHeight*0.5;

                        playerExploded.setFrame(i);
                        playerExploded.setRect(positionX, positionY);
                        playerExploded.draw(screen);
                        SDL_RenderPresent(screen);
                    }
                        deadTimes++;
                        if (deadTimes <= 3)
                        {
                            //respawn
                            player.setRect(0, 0);
                            Mix_PlayChannel(-1, playerExplodedSound, 0);
                            player.setTimeBack(60);
                            SDL_Delay(1000);//1s
                            playerLifeValue--;//player life deduct
                            continue;
                        }
                        else
                        {
                            //destroy end quit for now
                            //display messagebox
                            if (MessageBox(NULL, L":( Good Luck Nextime", L"You Dead", MB_OK | MB_ICONEXCLAMATION) == IDOK)
                            {
                                
                                enemy->free();
                                close();
                                SDL_Quit();
                                return 0;
                            }

                        }
                    
                }

            }
        }
        int frameExploiWidth = enemyExploded.getFrameWidht();
        int frameExploiHeight = enemyExploded.getFrameHeight();

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
                            scoreValue++;//increase score when monster dead
                            //exploi first, when collide
                            for (int i = 0; i < 8; ++i)//run 8 frame
                            {
                                int positionX = playerBullet->getRect().x - frameExploiWidth*0.5;//when the bullet touch, exploi in center
                                int positionY = playerBullet->getRect().y - frameExploiHeight*0.5;
                                enemyExploded.setFrame(i);
                                enemyExploded.setRect(positionX, positionY);
                                enemyExploded.draw(screen);
                            }
                            //destroy
                            player.destroyBullet(t);
                            Mix_PlayChannel(-1, enemyExplodedSound, 0);
                            enemy->free();
                            listEnemies.erase(listEnemies.begin() + b);//remove the enemy
                        }
                    }
                }
            }
        }
        //display game time count
        std::string time = "Time: ";
        Uint32 timeValue = SDL_GetTicks() / 1000;
        Uint32 timeCount = 300 - timeValue;
        if (timeCount <= 0)
        {
            isQuit = true;
            break;
        }
        else
        {
            std::string value = std::to_string(timeCount);
            time += value;
            gameTimeCount.setText(time);
            gameTimeCount.loadText(font, screen);
            gameTimeCount.textRender(screen, screenWidth - 200, 15);//top right corner
        }
        std::string score = std::to_string(scoreValue);
        std::string scoreT("Monster Kill Score: ");
        scoreT += score;
        scoreCount.setText(scoreT);
        scoreCount.loadText(font, screen);
        scoreCount.textRender(screen, screenWidth*0.5 - 50, 15);//1/2 width -50, 15 y

        int diamondCount = player.getDiamondCount();
        std::string diamondString = std::to_string(diamondCount);
        diamondGCount.setText(diamondString);
        diamondGCount.loadText(font, screen);
        diamondGCount.textRender(screen, screenWidth*0.5 - 150, 15);//1/2 width -150, 15 y

        std::string life = std::to_string(playerLifeValue);
        std::string lifeT("Life: ");
        lifeT += life;
        playerLife.setText(lifeT);
        playerLife.loadText(font, screen);
        playerLife.textRender(screen, 20, 15);//20x, 15 y


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
