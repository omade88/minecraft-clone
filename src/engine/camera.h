class Camera {
public:
    Camera();
    void move(float deltaX, float deltaY, float deltaZ);
    glm::mat4 getViewMatrix() const;

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
};