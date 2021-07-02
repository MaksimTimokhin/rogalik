#include "direction.h"

const Direction Direction::kLeft = Direction(0, -1);
const Direction Direction::kRight = Direction(0, 1);
const Direction Direction::kUp = Direction(-1, 0);
const Direction Direction::kDown = Direction(1, 0);

int Direction::GetDY() const {
    return dy_;
}

int Direction::GetDX() const {
    return dx_;
}

Direction::Direction(int dy, int dx) : dy_(dy), dx_(dx) {
}