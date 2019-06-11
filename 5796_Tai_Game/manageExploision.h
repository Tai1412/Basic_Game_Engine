#pragma once
#ifndef MANAGE_EXPLOISION_H_
#define MANAGE_EXPLOISION_H_
//include
#include "parentFunction.h"
#include "Entity.h"
class manageExploision : public Entity
{
public:
    manageExploision();
    ~manageExploision();
public:
    void setClip();
    void setFrame(const int& sFrame)
    {
        frame = sFrame;
    }
    virtual bool loadImage(std::string path, SDL_Renderer* screen);//override from entity
    void draw(SDL_Renderer* screen);
    int getFrameWidht()
        const
    {
        return frameWidth;
    }
    int getFrameHeight()
        const
    {
        return frameHeight;
    }
private:
    int frameWidth;
    int frameHeight;
    int frame;
    SDL_Rect clipFrame[8];//frame 8
};
#endif
