#pragma once
#ifndef MANAGE_DISPLAY_THING_H_
#define MANAGE_DISPLAY_THING_H_
#include "parentFunction.h"
#include "Entity.h"
//manageDisplayThing such text, playerlife, time count,... relate to display 
class manageDisplayThing
{
public:
    manageDisplayThing();
    ~manageDisplayThing();
    enum colorText
    {
        textRed = 0,
        textWhite=1,
        textBlack=2,
    };
    bool loadText(TTF_Font* font, SDL_Renderer* screen);
    void free();
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setColor(int type);
    void textRender(SDL_Renderer* screen, int positionX, int positionY, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    int getWidth()
        const
    {
        return width;
    }
    int getHeight()
        const
    {
        return height;
    }
    void setText(const std::string& text)
    {
        value = text;
    }
    std::string getText()
        const
    {
        return value;
    }
private:
    std::string value;
    SDL_Color colorText;
    SDL_Texture* textTexture;
    int width;
    int height;
};
//draw icon score next to diamond score
class diamondScore:public Entity
{
public:
    diamondScore();
    ~diamondScore();
    
    void init(SDL_Renderer* screen);
    void draw(SDL_Renderer* screen);
    void setPosition(const int& posX, const int& posY)
    {
        positionX = posX;
        positionY = posY;
    }
private:
    int positionX;
    int positionY;
};

#endif

