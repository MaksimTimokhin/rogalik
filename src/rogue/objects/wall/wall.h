#pragma once

#include <rogue/objects/interactive_object.h>

class Wall : public IInteractiveObject {
public:
    Wall();

    bool IsMemorable() const override;

    wchar_t Draw() const override;
    bool IsTransparent() const override;
    void Interact(Hero &hero) override;
};