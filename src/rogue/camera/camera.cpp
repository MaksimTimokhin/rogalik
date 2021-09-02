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

void Camera::SetYLimit(int y_limit) {
    y_limit_ = y_limit;
}

void Camera::SetXLimit(int x_limit) {
    x_limit_ = x_limit;
}

void Camera::SetPosition(int y, int x) {
    y_pos_ = std::max(0, std::min(y, y_limit_));
    x_pos_ = std::max(0, std::min(x, x_limit_));
}

void Camera::Move(const Direction &direction) {
    SetPosition(y_pos_ + direction.GetDY(), x_pos_ + direction.GetDX());
}