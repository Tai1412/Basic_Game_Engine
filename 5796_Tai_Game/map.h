#pragma once
#ifndef MAP_H_
#define MAP_H_
#include "parentFunction.h"
#include "Entity.h"
class tileMat :
	public Entity
{
public:
	tileMat(){ ; }
	~tileMat(){ ; }
};
class Map
{
public:
	Map(){ ; }
	~Map(){ ; }
	void loadMyMap(char* mapName);//read all information in map
	void drawMyMap(SDL_Renderer* des);//draw
	void loadMyMapTiles(SDL_Renderer* screen);//load all image of tile mat
	myMap getMyMap() const
	{
		return gameMap;
	}
	void setMyMap(myMap& mapData)
	{
		gameMap = mapData;
	}
private:
	myMap gameMap;
	tileMat tileMat[maxTiles];//20
};
#endif

