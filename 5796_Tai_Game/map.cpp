#include "map.h"


void Map::loadMyMap(char* mapName)
{
	gameMap.maxX = 0;//start count from cell 0
	gameMap.maxY = 0;
	FILE* file = NULL; //read file
	fopen_s(&file, mapName, "rb");//read mode rb
	if (file == NULL)//check file
	{
		return;
	}
	for (int i = 0; i < maxMapY; i++)//<10 rows
	{
		for (int j = 0; j < maxMapX; j++)
		{
			fscanf_s(file, "%d", &gameMap.tile[i][j]);
			if (gameMap.tile[i][j] > 0)//take until last elements
			{
				if (j > gameMap.maxX)
				{
					gameMap.maxX = j;
				}

				if (i > gameMap.maxY)
				{
					gameMap.maxY = i;
				}
			}
		}
	}
	gameMap.maxX = (gameMap.maxX + 1)*tileSize; // 25600=>400x64
	gameMap.maxY = (gameMap.maxY + 1)*tileSize;//10*64=640
	gameMap.startX = gameMap.startY = 0;
	gameMap.fileName = mapName;//save in case reload
	fclose(file);
}
void Map::loadMyMapTiles(SDL_Renderer* screen)
{
	char fileImage[30];
	FILE *file = NULL;

	for (int i = 0; i < maxTiles; i++)
	{
		sprintf_s(fileImage, "assets/myMap/%d.png", i);
		fopen_s(&file, fileImage, "rb");//check

		if (file == NULL)
		{
			continue;//iff image null jut skip
		}

		fclose(file);

		tileMat[i].loadImage(fileImage, screen);
	}
}
void Map::drawMyMap(SDL_Renderer* des)
{
	int mapX = 0;
	int x1 = 0;
	int x2 = 0;

	int mapY = 0;
	int y1 = 0;
	int y2 = 0;

	mapX = gameMap.startX / tileSize;
	x1 = (gameMap.startX %tileSize)*-1;
	x2 = x1 + screenWidth + (x1 == 0 ? 0 : tileSize);
	mapY = gameMap.startY / tileSize;
	y1 = (gameMap.startY%tileSize)*-1;
	y2 = y1 + screenHeight + (y1 == 0 ? 0 : tileSize);

	for (int i = y1; i < y2; i += tileSize)
	{
		mapX = gameMap.startX / tileSize;
		for (int j = x1; j < x2; j += tileSize)
		{
			int value = gameMap.tile[mapY][mapX];
			if (value != 0)
			{
				tileMat[value].setRect(j, i);
				tileMat[value].render(des);
			}
			mapX++;
		}
		mapY++;
	}
}
