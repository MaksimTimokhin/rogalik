#pragma once

#include <rogue/objects/movable_object.h>

#include <vector>

class Hero : public AbstractMovableObject {
public:
    Hero(int dungeon_height, int dungeon_width, int y_pos, int x_pos);
    wchar_t Draw() const override;

    void Memorize(int y_pos, int x_pos);
    void Forget(int y_pos, int x_pos);
    bool Remembers(int y_pos, int x_pos) const;

private:
    int health_ = 100;
    std::vector<std::vector<bool>> memory_;
};