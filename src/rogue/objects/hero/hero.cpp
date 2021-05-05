#include "hero.h"

Hero::Hero(int y_pos, int x_pos) : AbstractMovableObject(y_pos, x_pos) {
}

wchar_t Hero::Draw() const {
    if (health_ >= 90) {
        return L'😎';
    }
    if (health_ >= 70) {
        return L'😄';
    }
    if (health_ >= 50) {
        return L'😌';
    }
    if (health_ >= 30) {
        return L'😐';
    }
    if (health_ >= 20) {
        return L'😳';
    }
    if (health_ >= 10) {
        return L'😬';
    }
    if (health_ >= 0) {
        return L'😰';
    }
    return L'😵';
}