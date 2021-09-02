#include <rogue/rogue_game.h>

#include <iostream>

int main() {
    try {
        RogueGame game(6, 20, 50);
        game.Run();
    } catch (const std::exception &e) {
        std::cerr << e.what();
    }
}