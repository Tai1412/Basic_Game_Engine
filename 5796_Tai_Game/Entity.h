#pragma once
#ifndef ENTITY_H_
#define ENTITY_H_
//include
#include "parentFunction.h"
class Entity
{
public:
	Entity();
	~Entity();

	//set recct
	void setRect(const int& x, const int& y)
	{
		rect.x = x;
		rect.y = y;
	}
	//get rect
	SDL_Rect getRect()
		const 
	{
		return rect;
	}
	//get object
	SDL_Texture* getObject() 
	{ 
		return object;
	}
	//load image	//directory path  //screen
    virtual  bool loadImage(std::string path, SDL_Renderer* screen);
	//Render
	void render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void free();//free space
protected:
	SDL_Texture* object;
	SDL_Rect rect;
};

#endif

