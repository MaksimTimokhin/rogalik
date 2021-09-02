#include "wall.h"

Wall::Wall(){};

wchar_t Wall::Draw() const {
    return L'🧱';
}

bool Wall::CanMove() const {
    return false;
}

bool Wall::IsTransparent() const {
    return false;
}

void Wall::Interact(Hero &hero) {
}