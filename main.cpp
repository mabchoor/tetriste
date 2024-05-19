#include "src/GameCycle.h"

int main() {
    // Create an instance of the GameCycle class
    GameCycle& Game = GameCycle::getInstance();

    // Initialize the game
    Game.init();

    // Run the game
    Game.run();

    // Close the game
    Game.close();

    return 0;
}
