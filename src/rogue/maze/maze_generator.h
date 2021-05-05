#pragma once

#include <rogue/dungeon/dungeon.h>

class MazeGenerator {
public:
    static std::unique_ptr<Dungeon> GenerateMaze(int block_size, int y_blocks, int x_blocks);

private:
    static constexpr double kWallProbability = 0.8;
};