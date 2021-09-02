#pragma once

#include <rogue/direction/direction.h>
#include <rogue/dungeon/dungeon.h>

class MazeGenerator {
public:
    static std::unique_ptr<Dungeon> GenerateMaze(int block_size, int y_blocks, int x_blocks);

private:
    static void SpawnFence(Dungeon *dungeon, int y_pos, int x_pos, const Direction &direction,
                           int length);

private:
    static const double kWallProbability;
};