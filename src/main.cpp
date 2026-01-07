#include <iostream>
#include "engine/renderer.h"
#include "world/world.h"
#include "player/player.h"

int main() {
    Renderer renderer;
    World world;
    Player player;

    // Initialize the game engine
    if (!renderer.init()) {
        std::cerr << "Failed to initialize the renderer!" << std::endl;
        return -1;
    }

    // Load the game world
    world.load();

    // Main game loop
    while (true) {
        // Handle player input
        player.move();

        // Update the world
        world.update();

        // Render the world
        renderer.render(world, player);

        // Check for exit condition (placeholder)
        if (/* exit condition */) {
            break;
        }
    }

    // Cleanup
    renderer.cleanup();
    return 0;
}