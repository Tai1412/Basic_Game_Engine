#include "parentFunction.h"

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