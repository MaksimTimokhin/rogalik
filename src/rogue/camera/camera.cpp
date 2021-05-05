#include "camera.h"

#include <algorithm>

Camera::Camera(int y_limit, int x_limit) : y_limit_(y_limit), x_limit_(x_limit) {
}

int Camera::GetYPos() const {
    return y_pos_;
}

int Camera::GetXPos() const {
    return x_pos_;
}

void Camera::SetPosition(int y, int x) {
    y_pos_ = std::min(y, y_limit_);
    x_pos_ = std::min(x, x_limit_);
}

void Camera::MoveLeft() {
    if (x_pos_ > 0) {
        --x_pos_;
    }
}

void Camera::MoveRight() {
    if (x_pos_ < x_limit_) {
        ++x_pos_;
    }
}

void Camera::MoveDown() {
    if (y_pos_ < y_limit_) {
        ++y_pos_;
    }
}

void Camera::MoveUp() {
    if (y_pos_ > 0) {
        --y_pos_;
    }
}
