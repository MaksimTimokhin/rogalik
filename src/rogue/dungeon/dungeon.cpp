#include "dungeon.h"

Dungeon::Dungeon(int height, int width) {
    dungeon_.resize(height);
    for (auto &t : dungeon_) {
        t.resize(width);
    }
}

int Dungeon::GetHeight() const {
    return dungeon_.size();
}

int Dungeon::GetWidth() const {
    if (!GetHeight()) {
        return 0;
    }
    return dungeon_[0].size();
}

void Dungeon::SpawnObject(int y_pos, int x_pos, std::unique_ptr<IInteractiveObject> &&object) {
    dungeon_[y_pos][x_pos] = std::move(object);
}

IInteractiveObject *Dungeon::GetObject(int y_pos, int x_pos) {
    if (y_pos >= GetHeight() || x_pos >= GetWidth()) {
        return nullptr;
    }
    return dungeon_[y_pos][x_pos].get();
}