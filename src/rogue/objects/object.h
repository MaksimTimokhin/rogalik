#pragma once

class Hero;

class IObject {
public:
    virtual wchar_t Draw() const = 0;
    virtual bool IsTransparent() const = 0;
    virtual bool CanMove() const = 0;
    virtual void Interact(Hero &hero) = 0;
    virtual ~IObject() = default;
};