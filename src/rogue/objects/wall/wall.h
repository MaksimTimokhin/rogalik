#pragma once

#include <rogue/objects/interactive_object.h>

class Wall : public IInteractiveObject {
public:
    Wall();
    wchar_t Draw() const override;
    void Interact(Hero &hero) override;
};