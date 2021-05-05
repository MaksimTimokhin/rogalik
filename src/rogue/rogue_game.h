#pragma once

#include <application/application.h>
#include <rogue/camera/camera.h>
#include <rogue/maze/maze_generator.h>
#include <rogue/objects/hero/hero.h>

class RogueGame : public AbstractApplication {
public:
    RogueGame(int dungeon_block_size, int dungeon_y_blocks, int dungeon_x_blocks);

protected:
    void Init() override;
    void UpdateState(int key) override;
    void DrawFrame() override;

private:
    void DrawCurrentView();
    void DrawHero();

    void DrawObject(int y_pos, int x_pos);

    int GetObjectScreenYPos(int y_pos) const;
    int GetObjectScreenXPos(int x_pos) const;

    bool IsCellOnEdgeOfScreen(int y_pos, int x_pos) const;
    bool MoveElseInteract(int y_pos, int x_pos);

    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();

private:
    const int kDungeonBlockSize;
    const int kDungeonYBlocks;
    const int kDungeonXBlocks;

    Hero hero_{1, 1};
    std::unique_ptr<Dungeon> dungeon_ =
        MazeGenerator::GenerateMaze(kDungeonBlockSize, kDungeonYBlocks, kDungeonXBlocks);
    Camera camera_{dungeon_->GetHeight() - screen_height_ + 1,
                   dungeon_->GetWidth() - (screen_width_ - 1) / 2};
};