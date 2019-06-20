#include "parentFunction.h"
#include "manageDisplayThing.h"

int parentFunction::menu(SDL_Renderer* screen, TTF_Font* font)
{
    int time = 0;
    int valueX = 0;
    int valueY = 0;
    Entity myMenu;
    bool reUer = myMenu.loadImage("assets//background//myBackgroundMenu.png",screen);
    const int menuNumber = 3;
    SDL_Rect position[menuNumber];
    position[0].x = screenWidth*0.3 - 150;
    position[0].y = screenHeight*0.8 - 40;
    position[1].x = screenWidth*0.3 - 150;
    position[1].y = screenHeight*0.8 + 40;
    position[2].x = screenWidth*0.3 - 150;
    position[2].y = screenHeight*0.8 + 80;
    manageDisplayThing menuText[menuNumber];
    menuText[0].setText("Play Game");
    menuText[0].setColor(manageDisplayThing::textBlack);
    menuText[0].loadText(font, screen);

    menuText[1].setText("How To Play");
    menuText[1].setColor(manageDisplayThing::textBlack);
    menuText[1].loadText(font, screen);

    menuText[2].setText("Exit");
    menuText[2].setColor(manageDisplayThing::textBlack);
    menuText[2].loadText(font, screen);

    bool selected[menuNumber] = { 0, 0 ,0};//set initial
    SDL_Event event;
    while (true)
    {
        time = SDL_GetTicks();
        
       
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT://out
                menuText[0].free();
                menuText[0].free();
                myMenu.free();
                return 2;
            case SDL_MOUSEMOTION://move moue
               valueX = event.motion.x;
               valueY = event.motion.y;
               for (int i = 0; i < menuNumber; ++i)
               {
                   if (valueX >= position[i].x && valueX <= position[i].x + position[i].w &&
                       valueY >= position[i].y && valueY <= position[i].y + position[i].h)
                   {
                       if (!selected[i])
                       {
                           selected[i] = 2;
                           menuText[i].setColor(manageDisplayThing::textRed);
                           menuText[i].loadText(font, screen);
                       }
                   }
                   else
                   {
                       if (selected[i])
                       {
                           selected[i] = 0;
                           menuText[i].free();
                           menuText[i].setColor(manageDisplayThing::textBlack);
                           menuText[i].loadText(font, screen);
                       }
                   }
               }
               break;
            case SDL_MOUSEBUTTONDOWN:
                valueX = event.button.x;
                valueY = event.button.y;
                for (int i = 0; i < menuNumber; ++i) {
                    if (valueX >= position[i].x && valueX <= position[i].x + position[i].w &&
                        valueY >= position[i].y && valueY <= position[i].y + position[i].h)
                    {
                        menuText[0].free();
                        menuText[1].free();
                        menuText[2].free();
                        myMenu.free();
                        return i;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    menuText[0].free();
                    menuText[1].free();
                    menuText[2].free();
                    myMenu.free();
                    return 2;
                }
            }
        }
        myMenu.render(screen, NULL);
        for (int i = 0; i < menuNumber; ++i)
        {
            menuText[i].textRender(screen, position[i].x, position[i].y);
            position[i].w = menuText[i].getWidth();
            position[i].h = menuText[i].getHeight();
        }
        SDL_RenderPresent(screen);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }
    return 0;


}
bool parentFunction::entityColliseChecking(const SDL_Rect& entity1, const SDL_Rect& entity2)
{
    int leftA = entity1.x;
    int rightA = entity1.x + entity1.w;
    int topA = entity1.y;
    int bottomA = entity1.y + entity1.h;

    int leftB = entity2.x;
    int rightB = entity2.x + entity2.w;
    int topB = entity2.y;
    int bottomB = entity2.y + entity2.h;

    // Case 1: size entity 1 < size entity 2
    if (leftA > leftB && leftA < rightB)
    {
        if (topA > topB && topA < bottomB)
        {
            return true;
        }
    }

    if (leftA > leftB && leftA < rightB)
    {
        if (bottomA > topB && bottomA < bottomB)
        {
            return true;
        }
    }

    if (rightA > leftB && rightA < rightB)
    {
        if (topA > topB && topA < bottomB)
        {
            return true;
        }
    }

    if (rightA > leftB && rightA < rightB)
    {
        if (bottomA > topB && bottomA < bottomB)
        {
            return true;
        }
    }

    // Case 2: size entity 1 < size entity 2
    if (leftB > leftA && leftB < rightA)
    {
        if (topB > topA && topB < bottomA)
        {
            return true;
        }
    }

    if (leftB > leftA && leftB < rightA)
    {
        if (bottomB > topA && bottomB < bottomA)
        {
            return true;
        }
    }

    if (rightB > leftA && rightB < rightA)
    {
        if (topB > topA && topB < bottomA)
        {
            return true;
        }
    }

    if (rightB > leftA && rightB < rightA)
    {
        if (bottomB > topA && bottomB < bottomA)
        {
            return true;
        }
    }

    // Case 3: size entity 1 == size entity 2
    if (topA == topB && rightA == rightB && bottomA == bottomB)
    {
        return true;
    }

    return false;
}