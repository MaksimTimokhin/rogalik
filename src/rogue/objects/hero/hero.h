#pragma once

#include <rogue/objects/movable_object.h>

class Hero : public AbstractMovableObject {
public:
    Hero(int y_pos, int x_pos);
    wchar_t Draw() const override;

private:
    int health_ = 100;
};