#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine/renderer.h"
#include "engine/camera.h"
#include "world/world.h"
#include "player/player.h"

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Minecraft Clone", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW!" << std::endl;
        return -1;
    }

    // Set viewport
    glViewport(0, 0, 1280, 720);

    // Initialize game components
    Renderer renderer;
    World world;
    Player player;
    Camera camera;

    renderer.init();
    world.load();

    // Main game loop
    float lastFrame = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        // Calculate delta time
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Handle input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        // Process player input
        float moveSpeed = 2.5f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            player.move(0.0f, 0.0f, -moveSpeed);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            player.move(0.0f, 0.0f, moveSpeed);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            player.move(-moveSpeed, 0.0f, 0.0f);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            player.move(moveSpeed, 0.0f, 0.0f);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            player.move(0.0f, moveSpeed, 0.0f);
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            player.move(0.0f, -moveSpeed, 0.0f);

        // Update world
        world.update();

        // Render
        renderer.render(camera);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    renderer.cleanup();
    glfwTerminate();
    return 0;
}