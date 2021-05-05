#pragma once

#include <rogue/objects/interactive_object.h>

#include <memory>
#include <vector>

class Dungeon {
public:
    Dungeon(int height, int width);

    int GetHeight() const;
    int GetWidth() const;

    void SpawnObject(int y_pos, int x_pos, std::unique_ptr<IInteractiveObject> &&object);
    IInteractiveObject *GetObject(int y_pos, int x_pos);

private:
    std::vector<std::vector<std::unique_ptr<IInteractiveObject>>> dungeon_;
};