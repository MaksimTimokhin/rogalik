#pragma once

class IObject {
public:
    virtual wchar_t Draw() const = 0;
    virtual ~IObject() = default;
};