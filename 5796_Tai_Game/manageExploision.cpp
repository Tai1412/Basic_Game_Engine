#include "manageExploision.h"


manageExploision::manageExploision()
{
    //constructor
    frameWidth = 0;
    frameHeight = 0;
    frame = 0;
}


manageExploision::~manageExploision()
{
}

bool manageExploision::loadImage(std::string path, SDL_Renderer* screen)
{
    bool reUse = Entity::loadImage(path, screen);
    if (reUse)
    {
        frameWidth = rect.w / 8;
        frameHeight = rect.h;
    }
    return reUse;
}
void manageExploision::setClip()
{
    if (frameWidth > 0 && frameHeight > 0)
    {
        clipFrame[0].x = 0;
        clipFrame[0].y = 0;
        clipFrame[0].w = frameWidth;
        clipFrame[0].h = frameHeight;

        clipFrame[1].x = frameWidth;
        clipFrame[1].y = 0;
        clipFrame[1].w = frameWidth;
        clipFrame[1].h = frameHeight;

        clipFrame[2].x = frameWidth * 2;
        clipFrame[2].y = 0;
        clipFrame[2].w = frameWidth;
        clipFrame[2].h = frameHeight;

        clipFrame[3].x = frameWidth * 3;
        clipFrame[3].y = 0;
        clipFrame[3].w = frameWidth;
        clipFrame[3].h = frameHeight;

        clipFrame[4].x = frameWidth * 4;
        clipFrame[4].y = 0;
        clipFrame[4].w = frameWidth;
        clipFrame[4].h = frameHeight;

        clipFrame[5].x = frameWidth * 5;
        clipFrame[5].y = 0;
        clipFrame[5].w = frameWidth;
        clipFrame[5].h = frameHeight;

        clipFrame[6].x = frameWidth * 6;
        clipFrame[6].y = 0;
        clipFrame[6].w = frameWidth;
        clipFrame[6].h = frameHeight;

        clipFrame[7].x = frameWidth * 7;
        clipFrame[7].y = 0;
        clipFrame[7].w = frameWidth;
        clipFrame[7].h = frameHeight;
    }
}
void manageExploision::draw(SDL_Renderer* screen)
{
    //draw
    SDL_Rect* thisClip = &clipFrame[frame];
    SDL_Rect rect_ = 
    {
        rect.x,
        rect.y,
        frameWidth,
        frameHeight
    };
    if (thisClip != NULL)
    {
        rect_.w = thisClip->w;
        rect_.h = thisClip->h;
    }
    SDL_RenderCopy(screen, object, thisClip, &rect_);
}