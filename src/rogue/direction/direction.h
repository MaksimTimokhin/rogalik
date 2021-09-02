#pragma once

#include <random>

class Direction {
public:
    static const Direction kLeft;
    static const Direction kRight;
    static const Direction kUp;
    static const Direction kDown;

    template <typename RandomGenerator>
    static Direction GetRandomDirection(RandomGenerator &gen) {
        switch (std::uniform_int_distribution(0, 3)(gen)) {
            case 0:
                return kLeft;
            case 1:
                return kRight;
            case 2:
                return kUp;
            case 3:
                return kDown;
        }
        // unreachable
        return Direction(0, 0);
    }

    int GetDY() const;
    int GetDX() const;

private:
    Direction(int dy, int dx);

private:
    int dy_;
    int dx_;
};