#pragma once

#include <cstddef>

class Camera {
public:
    Camera(int y_limit, int x_limit);

    int GetYPos() const;
    int GetXPos() const;

    void SetPosition(int y, int x);

    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();

private:
    int y_pos_ = 0;
    int x_pos_ = 0;

    const int y_limit_;
    const int x_limit_;
};