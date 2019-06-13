#include "manageDisplayThing.h"

manageDisplayThing::manageDisplayThing()
{
    //white
    colorText.r = 255;
    colorText.g = 255;
    colorText.b = 255;
    textTexture = NULL;
}


manageDisplayThing::~manageDisplayThing()
{
}

bool manageDisplayThing::loadText(TTF_Font* font, SDL_Renderer* screen)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, value.c_str(), colorText);
    if (textSurface)
    {
        textTexture = SDL_CreateTextureFromSurface(screen, textSurface);
        width = textSurface->w;
        height = textSurface->h;
        SDL_FreeSurface(textSurface);
    }
    return textTexture != NULL;//true

}
void manageDisplayThing::free()
{
    if (textTexture != NULL)
    {
        SDL_DestroyTexture(textTexture);
        textTexture = NULL;
    }
}
void manageDisplayThing::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    colorText.r = red;
    colorText.g = green;
    colorText.b = blue;
}
void manageDisplayThing::setColor(int type)
{
    if (type == textRed)
    {
        SDL_Color colour = { 255, 0, 0 };//red
        colorText = colour;
    }
    else if (type == textWhite)
    {
        SDL_Color colour = { 255, 255 ,255 };//white
        colorText = colour;
    }
    else if (type == textBlack)
    {
        SDL_Color colour = { 0, 0, 0 };//black
        colorText = colour;
    }
}
void manageDisplayThing::textRender(SDL_Renderer* screen, int positionX, int positionY, SDL_Rect* clip, double angle, SDL_Point* center , SDL_RendererFlip flip)
{
    SDL_Rect rect_ =
    {
        positionX, positionY,
        width,
        height
    };
    if (clip != NULL)
    {
        rect_.w = clip->w;
        rect_.h = clip->h;
    }
    SDL_RenderCopyEx(screen, textTexture, clip, &rect_, angle,center, flip);
}
diamondScore::diamondScore()
{
    //constructor
    positionX = 0;
    positionY = 0;
}
diamondScore::~diamondScore()
{

}
void diamondScore::init(SDL_Renderer* screen)
{
    loadImage("assets//myMap//4.png", screen);
}
void diamondScore::draw(SDL_Renderer* screen)
{
    rect.x = positionX;
    rect.y = positionY;
    render(screen);
}