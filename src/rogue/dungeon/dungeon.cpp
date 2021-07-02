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

void Dungeon::SpawnObject(int y_pos, int x_pos, std::unique_ptr<IObject> &&object) {
    dungeon_[y_pos][x_pos] = std::move(object);
}

std::unique_ptr<IObject> Dungeon::RemoveObject(int y_pos, int x_pos) {
    if (y_pos < 0 || y_pos >= GetHeight() || x_pos < 0 || x_pos >= GetWidth()) {
        return {};
    }
    return std::move(dungeon_[y_pos][x_pos]);
}

IObject *Dungeon::GetObject(int y_pos, int x_pos) {
    if (y_pos >= GetHeight() || x_pos >= GetWidth()) {
        return nullptr;
    }
    return dungeon_[y_pos][x_pos].get();
}

const IObject *Dungeon::GetObject(int y_pos, int x_pos) const {
    if (y_pos >= GetHeight() || x_pos >= GetWidth()) {
        return nullptr;
    }
    return dungeon_[y_pos][x_pos].get();
}