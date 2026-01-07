#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

class Player {
public:
    Player();
    void move(float deltaX, float deltaY, float deltaZ);
    void handleInput(float deltaTime);
    glm::vec3 getPosition() const;

private:
    glm::vec3 position;
    glm::vec3 velocity;
    float speed;
};

#endif // PLAYER_H