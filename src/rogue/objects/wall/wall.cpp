#include "wall.h"

Wall::Wall(){};

wchar_t Wall::Draw() const {
    return L'🧱';
}

bool Wall::IsMemorable() const {
    return true;
}

bool Wall::IsTransparent() const {
    return false;
}

void Wall::Interact(Hero &hero) {
}