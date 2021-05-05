#pragma once

#include "object.h"

class AbstractMovableObject : public IObject {
public:
    AbstractMovableObject(int y_pos, int x_pos);

    int GetYPos() const;
    int GetXPos() const;

    void SetYPos(int y_pos);
    void SetXPos(int x_pos);

    virtual ~AbstractMovableObject() = default;

private:
    int y_pos_;
    int x_pos_;
};