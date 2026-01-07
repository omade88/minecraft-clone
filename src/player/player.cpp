#include "player.h"

Player::Player() : position(0.0f, 0.0f, 0.0f) {}

void Player::move(float deltaX, float deltaY, float deltaZ) {
    position.x += deltaX;
    position.y += deltaY;
    position.z += deltaZ;
}

glm::vec3 Player::getPosition() const {
    return position;
}