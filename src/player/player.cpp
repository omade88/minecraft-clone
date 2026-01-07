#include "player.h"

Player::Player() 
    : position(0.0f, 0.0f, 0.0f), 
      velocity(0.0f, 0.0f, 0.0f),
      speed(5.0f) {}

void Player::move(float deltaX, float deltaY, float deltaZ) {
    position.x += deltaX;
    position.y += deltaY;
    position.z += deltaZ;
}

void Player::handleInput(float deltaTime) {
    // Input handling can be implemented here
    // This method can be used for more complex input processing
}

glm::vec3 Player::getPosition() const {
    return position;
}