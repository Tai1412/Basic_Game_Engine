#include "parentFunction.h"
#include "Entity.h"
#include "map.h"
#include "playerObject.h"
#include <iostream>

Entity myBackground;
Map myGameMap;
playerObject player;
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
	window = SDL_CreateWindow("5796_Tai_Game", SDL_WINDOWPOS_CENTERED,
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

	while (!isQuit)
	{
		while (SDL_PollEvent(&_event) != 0)
		{
			if (_event.type == SDL_QUIT)
			{
				isQuit = true;
			}
			player.handleInputEvent(_event, screen);
		}
		SDL_RenderClear(screen);
		myBackground.render(screen, NULL);
		//myGameMap.drawMyMap(screen);//render map to screen
		myMap mapData = myGameMap.getMyMap();
		player.setMyMapXY(mapData.startX, mapData.startY);
		player.calMovePlayer(mapData);
		player.draw(screen);
		myGameMap.setMyMap(mapData);
		myGameMap.drawMyMap(screen);
		SDL_RenderPresent(screen);
	}
	close();
	system("pause");
	return 0;
}
