#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include <string>

struct Button
{
    Rectangle bounds;
    std::string text;

    bool isHovered(Vector2 mousePos) const
    {
        return CheckCollisionPointRec(mousePos, bounds);
    }
};

#endif
