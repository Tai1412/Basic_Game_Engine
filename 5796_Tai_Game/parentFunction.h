//define
#ifndef PARENT_FUNCTION_H_
#define PARENT_FUNCTION_H_
//will include every library instead of main
#include <Windows.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>//image
#include <SDL_mixer.h.>//sound
#include <SDL_ttf.h>//font
#include "Entity.h"
using namespace std;

static SDL_Window* window = NULL;
static SDL_Renderer* screen = NULL;
static SDL_Event _event;

//screen size
const int screenWidth = 1280;//full width
const int screenHeight = 640;//full heigth 

//define 
#define tileSize 64 //height of the screen 64x10=640
#define maxMapX 400 //set max map x =400
#define maxMapY 10 //max map y=10
#define maxTiles 20
//struct
typedef struct myMap
{
	//data member
	int startX;
	int startY;
	int maxX;
	int maxY;
	char* fileName;
	int tile[maxMapX][maxMapY];//400*10=4000
} myMap;//object
#endif