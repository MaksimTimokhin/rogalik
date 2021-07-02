#pragma once

#include <rogue/dungeon/dungeon.h>
#include <rogue/objects/creatures/creature.h>

#include <vector>

class Hero : public AbstractCreature {
public:
    Hero(Dungeon *dungeon, int y_pos, int x_pos);

    wchar_t Draw() const override;

    void Memorize(int y_pos, int x_pos);
    void Forget(int y_pos, int x_pos);
    bool Remembers(int y_pos, int x_pos) const;

    static Hero *SpawnHero(Dungeon *dungeon, int y_pos = 1, int x_pos = 1);

private:
    std::vector<std::vector<bool>> memory_;
};