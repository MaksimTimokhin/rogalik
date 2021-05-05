#pragma once

#include <cstddef>

class Camera {
public:
    Camera(int y_limit, int x_limit);

    int GetYPos() const;
    int GetXPos() const;

    void SetYLimit(int y_limit);
    void SetXLimit(int x_limit);

    void SetPosition(int y, int x);

    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();

private:
    int y_pos_ = 0;
    int x_pos_ = 0;

    int y_limit_;
    int x_limit_;
};