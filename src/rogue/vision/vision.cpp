#include "vision.h"

#include <cmath>
#include <stdexcept>

Vision::Vision(const Dungeon &dungeon) : dungeon_(dungeon) {
}

void Vision::CalculateVisibilityMap(int hero_y, int hero_x) {
    hero_y_ = hero_y;
    hero_x_ = hero_x;
    invisibile_cones_.Reset();
    map_.assign(dungeon_.GetHeight(), std::vector<bool>(dungeon_.GetWidth()));
    map_[hero_y_][hero_x_] = true;

    for (int i = 1;; ++i) {
        bool found_visible_cell = false;
        std::vector<std::pair<int, int>> walls;
        for (int j = 0; j < i; ++j) {
            found_visible_cell |= ProcessCell(hero_y_ - i, hero_x_ + j);
            found_visible_cell |= ProcessCell(hero_y_ + j, hero_x_ + i);
            found_visible_cell |= ProcessCell(hero_y_ + i, hero_x_ - j);
            found_visible_cell |= ProcessCell(hero_y_ - j, hero_x_ - i);
            found_visible_cell |= ProcessCell(hero_y_ - i, hero_x_ - j);
            found_visible_cell |= ProcessCell(hero_y_ - j, hero_x_ + i);
            found_visible_cell |= ProcessCell(hero_y_ + i, hero_x_ + j);
            found_visible_cell |= ProcessCell(hero_y_ + j, hero_x_ - i);
        }
        found_visible_cell |= ProcessCell(hero_y_ - i, hero_x_ + i);
        found_visible_cell |= ProcessCell(hero_y_ + i, hero_x_ + i);
        found_visible_cell |= ProcessCell(hero_y_ + i, hero_x_ - i);
        found_visible_cell |= ProcessCell(hero_y_ - i, hero_x_ - i);

        if (!found_visible_cell) {
            return;
        }
    }
}

bool Vision::IsCellVisible(int y_pos, int x_pos) const {
    if (y_pos < 0 || x_pos < 0 || y_pos >= dungeon_.GetHeight() || x_pos >= dungeon_.GetWidth()) {
        return true;
    }
    return map_[y_pos][x_pos];
}

bool Vision::ProcessCell(int y_pos, int x_pos) {
    if (y_pos < 0 || x_pos < 0 || y_pos >= dungeon_.GetHeight() || x_pos >= dungeon_.GetWidth()) {
        return false;
    }

    map_[y_pos][x_pos] = !invisibile_cones_.IsConeCovered(GetCellCone(y_pos, x_pos));
    if (auto object = dungeon_.GetObject(y_pos, x_pos); object && !object->IsTransparent()) {
        invisibile_cones_.AddCone(GetCellCone(y_pos, x_pos));
    }

    return map_[y_pos][x_pos];
}

int sign(int x) {
    if (x < 0) {
        return -1;
    }
    if (x > 0) {
        return 1;
    }
    return 0;
}

Cone Vision::GetUnitSquareCone(int y_center, int x_center) {
    if (x_center == 0) {
        return Cone{std::atan2(y_center - 0.5 * sign(y_center), 0.5 * sign(y_center)),
                    std::atan2(y_center - 0.5 * sign(y_center), -0.5 * sign(y_center))};
    }
    if (y_center == 0) {
        return Cone{std::atan2(-0.5 * sign(x_center), x_center - 0.5 * sign(x_center)),
                    std::atan2(0.5 * sign(x_center), x_center - 0.5 * sign(x_center))};
    }
    double dx = 0.5 * sign(y_center);
    double dy = -0.5 * sign(x_center);
    return Cone{std::atan2(y_center + dy, x_center + dx), std::atan2(y_center - dy, x_center - dx)};
}

Cone Vision::GetCellCone(int wall_y, int wall_x) const {
    return GetUnitSquareCone(hero_y_ - wall_y, wall_x - hero_x_);
}