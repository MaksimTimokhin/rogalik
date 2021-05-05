#include "maze_generator.h"

#include <rogue/objects/wall/wall.h>

#include <random>

std::unique_ptr<Dungeon> MazeGenerator::GenerateMaze(int block_size, int y_blocks, int x_blocks) {
    static std::random_device seed_gen;
    static std::mt19937 gen(seed_gen());
    std::uniform_int_distribution<int> direction(0, 3);
    std::bernoulli_distribution wall(kWallProbability);

    auto dungeon = std::make_unique<Dungeon>(block_size * y_blocks + 1, block_size * x_blocks + 1);

    // create edge walls
    for (int y = 0; y < dungeon->GetHeight(); ++y) {
        dungeon->SpawnObject(y, 0, std::make_unique<Wall>());
        dungeon->SpawnObject(y, dungeon->GetWidth() - 1, std::make_unique<Wall>());
    }
    for (int x = 0; x < dungeon->GetWidth(); ++x) {
        dungeon->SpawnObject(0, x, std::make_unique<Wall>());
        dungeon->SpawnObject(dungeon->GetHeight() - 1, x, std::make_unique<Wall>());
    }

    for (int y = block_size; y + block_size < dungeon->GetHeight(); y += block_size) {
        for (int x = block_size; x + block_size < dungeon->GetWidth(); x += block_size) {
            if (wall(gen)) {
                int dx, dy;
                switch (direction(gen)) {
                    case 0:
                        dx = 1;
                        dy = 0;
                        break;
                    case 1:
                        dx = -1;
                        dy = 0;
                        break;
                    case 2:
                        dx = 0;
                        dy = 1;
                        break;
                    case 3:
                        dx = 0;
                        dy = -1;
                        break;
                }
                for (int i = 0; i <= block_size; ++i) {
                    dungeon->SpawnObject(y + i * dy, x + i * dx, std::make_unique<Wall>());
                }
            }
        }
    }

    return dungeon;
}