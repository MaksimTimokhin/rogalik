#pragma once

#include <rogue/objects/object.h>

#include <memory>
#include <vector>

class Dungeon {
public:
    Dungeon(int height, int width);

    int GetHeight() const;
    int GetWidth() const;

    void SpawnObject(int y_pos, int x_pos, std::unique_ptr<IObject> &&object);
    std::unique_ptr<IObject> RemoveObject(int y_pos, int x_pos);

    IObject *GetObject(int y_pos, int x_pos);
    const IObject *GetObject(int y_pos, int x_pos) const;

private:
    std::vector<std::vector<std::unique_ptr<IObject>>> dungeon_;
};