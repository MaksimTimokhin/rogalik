#include "rogue_game.h"

#include <sstream>

RogueGame::RogueGame(int dungeon_block_size, int dungeon_y_blocks, int dungeon_x_blocks)
    : kDungeonBlockSize(dungeon_block_size),
      kDungeonYBlocks(dungeon_y_blocks),
      kDungeonXBlocks(dungeon_x_blocks) {
    Init();
}

void RogueGame::Init() {
    hero_vision_.CalculateVisibilityMap(hero_.GetYPos(), hero_.GetXPos());
    DrawFrame();
}

void RogueGame::UpdateState(int key) {
    switch (key) {
        case 'H':
        case 'h':
            MoveLeft();
            CenterCamera();
            break;
        case 'J':
        case 'j':
            MoveDown();
            CenterCamera();
            break;
        case 'K':
        case 'k':
            MoveUp();
            CenterCamera();
            break;
        case 'L':
        case 'l':
            MoveRight();
            CenterCamera();
            break;
        case KEY_LEFT:
            camera_.MoveLeft();
            break;
        case KEY_DOWN:
            camera_.MoveDown();
            break;
        case KEY_UP:
            camera_.MoveUp();
            break;
        case KEY_RIGHT:
            camera_.MoveRight();
            break;
    }
    hero_vision_.CalculateVisibilityMap(hero_.GetYPos(), hero_.GetXPos());
};

void RogueGame::DrawFrame() {
    ClearScreen();
    DrawCurrentView();
    DrawHero();
}

void RogueGame::DrawCurrentView() {
    for (int y = 0; y < screen_height_; ++y) {
        for (int x = 0; x < screen_width_ / 2; ++x) {
            int x_pos = camera_.GetXPos() + x;
            int y_pos = camera_.GetYPos() + y;
            if (!hero_vision_.IsCellVisible(y_pos, x_pos) && !hero_.Remembers(y_pos, x_pos)) {
                DrawFog(y_pos, x_pos);
            } else {
                DrawObject(y_pos, x_pos);
                if (auto object = dungeon_->GetObject(y_pos, x_pos);
                    object && object->IsMemorable()) {
                    hero_.Memorize(y_pos, x_pos);
                }
            }
        }
    }
}

void RogueGame::DrawHero() {
    SetCell(GetObjectScreenYPos(hero_.GetYPos()), GetObjectScreenXPos(hero_.GetXPos()),
            hero_.Draw());
}

void RogueGame::DrawObject(int y_pos, int x_pos) {
    if (auto object = dungeon_->GetObject(y_pos, x_pos)) {
        SetCell(GetObjectScreenYPos(y_pos), GetObjectScreenXPos(x_pos), object->Draw());
    }
}

void RogueGame::DrawFog(int y_pos, int x_pos) {
    SetCell(GetObjectScreenYPos(y_pos), GetObjectScreenXPos(x_pos), L'░');
    SetCell(GetObjectScreenYPos(y_pos), GetObjectScreenXPos(x_pos) + 1, L'░');
}

int RogueGame::GetObjectScreenYPos(int y_pos) const {
    return y_pos - camera_.GetYPos();
}

int RogueGame::GetObjectScreenXPos(int x_pos) const {
    return 2 * (x_pos - camera_.GetXPos());
}

bool RogueGame::IsCellOnEdgeOfScreen(int y_pos, int x_pos) const {
    if (y_pos <= camera_.GetYPos() || x_pos <= camera_.GetXPos()) {
        return true;
    }
    if (GetObjectScreenYPos(y_pos) >= screen_height_ - 1 ||
        GetObjectScreenXPos(x_pos) >= screen_width_ - 3) {
        return true;
    }
    return false;
}

bool RogueGame::MoveElseInteract(int y_pos, int x_pos) {
    if (auto object = dungeon_->GetObject(y_pos, x_pos)) {
        object->Interact(hero_);
        return false;
    }
    hero_.SetYPos(y_pos);
    hero_.SetXPos(x_pos);
    return true;
}

void RogueGame::MoveLeft() {
    int y_pos = hero_.GetYPos();
    int x_pos = hero_.GetXPos() - 1;
    if (MoveElseInteract(y_pos, x_pos) && IsCellOnEdgeOfScreen(y_pos, x_pos)) {
        camera_.MoveLeft();
    }
}

void RogueGame::MoveRight() {
    int y_pos = hero_.GetYPos();
    int x_pos = hero_.GetXPos() + 1;
    if (MoveElseInteract(y_pos, x_pos) && IsCellOnEdgeOfScreen(y_pos, x_pos)) {
        camera_.MoveRight();
    }
}

void RogueGame::MoveUp() {
    int y_pos = hero_.GetYPos() - 1;
    int x_pos = hero_.GetXPos();
    if (MoveElseInteract(y_pos, x_pos) && IsCellOnEdgeOfScreen(y_pos, x_pos)) {
        camera_.MoveUp();
    }
}

void RogueGame::MoveDown() {
    int y_pos = hero_.GetYPos() + 1;
    int x_pos = hero_.GetXPos();
    if (MoveElseInteract(y_pos, x_pos) && IsCellOnEdgeOfScreen(y_pos, x_pos)) {
        camera_.MoveDown();
    }
}

void RogueGame::CenterCamera() {
    int hero_y_pos = hero_.GetYPos();
    int hero_x_pos = hero_.GetXPos();
    if (IsCellOnEdgeOfScreen(hero_y_pos, hero_x_pos)) {
        camera_.SetPosition(hero_y_pos - screen_height_ / 2, hero_x_pos - screen_width_ / 4);
    }
}

void RogueGame::HandleResize() {
    AbstractApplication::HandleResize();
    camera_.SetYLimit(dungeon_->GetHeight() - screen_height_);
    camera_.SetXLimit(dungeon_->GetWidth() - (screen_width_ - 1) / 2);
    DrawFrame();
}