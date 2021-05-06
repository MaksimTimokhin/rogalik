#include "hero.h"

Hero::Hero(int dungeon_height, int dungeon_width, int y_pos, int x_pos)
    : memory_(dungeon_height, std::vector<bool>(dungeon_width)),
      AbstractMovableObject(y_pos, x_pos) {
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

void Hero::Memorize(int y_pos, int x_pos) {
    memory_[y_pos][x_pos] = true;
}

void Hero::Forget(int y_pos, int x_pos) {
    memory_[y_pos][x_pos] = false;
}

bool Hero::Remembers(int y_pos, int x_pos) const {
    return memory_[y_pos][x_pos];
}