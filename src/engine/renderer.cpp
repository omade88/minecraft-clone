#include "renderer.h"
#include "shader.h"
#include "camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer() {
}

Renderer::~Renderer() {
}

void Renderer::init() {
    // Initialize OpenGL settings
    glEnable(GL_DEPTH_TEST);
    // Load and compile shaders
    shader.load("shaders/vertex.glsl", "shaders/fragment.glsl");
}

void Renderer::render(Camera& camera) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.use();
    
    // Set the view matrix from the camera
    glm::mat4 view = camera.getViewMatrix();
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    
    // Render the game world and objects here
}

void Renderer::cleanup() {
    // Cleanup resources if needed
}