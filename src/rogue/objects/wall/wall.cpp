#include "wall.h"

Wall::Wall(){};

wchar_t Wall::Draw() const {
    return L'🧱';
}

void Wall::Interact(Hero &hero) {
}