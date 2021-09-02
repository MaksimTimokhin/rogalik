#include "maze_generator.h"

#include <rogue/objects/wall/wall.h>

#include <array>
#include <random>

const double MazeGenerator::kWallProbability = 0.8;

std::unique_ptr<Dungeon> MazeGenerator::GenerateMaze(int block_size, int y_blocks, int x_blocks) {
    static std::random_device seed_gen;
    static std::mt19937 gen(seed_gen());
    std::bernoulli_distribution wall(kWallProbability);

    auto dungeon = std::make_unique<Dungeon>(block_size * y_blocks + 1, block_size * x_blocks + 1);

    // spawn edge walls
    for (int y = 0; y + block_size <= dungeon->GetHeight(); y += block_size) {
        SpawnFence(dungeon.get(), dungeon->GetHeight() - y - 1, 0, Direction::kUp, block_size);
        SpawnFence(dungeon.get(), y, dungeon->GetWidth() - 1, Direction::kDown, block_size);
    }
    for (int x = 0; x + block_size <= dungeon->GetWidth(); x += block_size) {
        SpawnFence(dungeon.get(), 0, x, Direction::kRight, block_size);
        SpawnFence(dungeon.get(), dungeon->GetHeight() - 1, dungeon->GetWidth() - x - 1,
                   Direction::kLeft, block_size);
    }

    for (int y = block_size; y + block_size < dungeon->GetHeight(); y += block_size) {
        for (int x = block_size; x + block_size < dungeon->GetWidth(); x += block_size) {
            if (wall(gen)) {
                SpawnFence(dungeon.get(), y, x, Direction::GetRandomDirection(gen), block_size + 1);
            }
        }
    }

    return dungeon;
}

void MazeGenerator::SpawnFence(Dungeon *dungeon, int y_pos, int x_pos, const Direction &direction,
                               int length) {
    for (int i = 0; i < length; ++i) {
        dungeon->SpawnObject(y_pos + i * direction.GetDY(), x_pos + i * direction.GetDX(),
                             std::make_unique<Wall>());
    }
}