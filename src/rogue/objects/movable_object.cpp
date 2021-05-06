#include "movable_object.h"

AbstractMovableObject::AbstractMovableObject(int y_pos, int x_pos) : y_pos_(y_pos), x_pos_(x_pos) {
}

bool AbstractMovableObject::IsMemorable() const {
    return false;
}

int AbstractMovableObject::GetYPos() const {
    return y_pos_;
}

int AbstractMovableObject::GetXPos() const {
    return x_pos_;
}

void AbstractMovableObject::SetYPos(int y_pos) {
    y_pos_ = y_pos;
}

void AbstractMovableObject::SetXPos(int x_pos) {
    x_pos_ = x_pos;
}