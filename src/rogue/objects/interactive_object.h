#pragma once

#include <rogue/objects/hero/hero.h>

#include "object.h"

class IInteractiveObject : public IObject {
public:
    virtual void Interact(Hero &hero) = 0;
    virtual ~IInteractiveObject() = default;
};