#pragma once

#include <rogue/objects/object.h>

class Wall : public IObject {
public:
    Wall();

    wchar_t Draw() const override;
    bool IsTransparent() const override;
    bool CanMove() const override;

    void Interact(Hero &hero) override;
};