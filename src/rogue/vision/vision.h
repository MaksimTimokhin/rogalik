#pragma once

#include <rogue/dungeon/dungeon.h>

#include "cone_union.h"

class Vision {
public:
    Vision(const Dungeon &dungeon);

    void CalculateVisibilityMap(int hero_y, int hero_x);
    bool IsCellVisible(int y_pos, int x_pos) const;

private:
    bool ProcessCell(int y_pos, int x_pos);
    Cone GetCellCone(int wall_y, int wall_x) const;
    static Cone GetUnitSquareCone(int x_center, int y_center);

private:
    const Dungeon &dungeon_;

    int hero_y_;
    int hero_x_;
    std::vector<std::vector<bool>> map_{
        static_cast<size_t>(dungeon_.GetHeight()),
        std::vector<bool>(static_cast<size_t>(dungeon_.GetWidth()))};
    ConeUnion invisibile_cones_;
};