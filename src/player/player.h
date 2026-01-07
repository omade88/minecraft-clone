class Player {
public:
    Player();
    void move(float deltaX, float deltaY, float deltaZ);
    glm::vec3 getPosition() const;

private:
    glm::vec3 position;
};