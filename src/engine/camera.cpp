#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(float fov, float aspect, float near, float far);
    void move(const glm::vec3& offset);
    glm::mat4 getViewMatrix() const;

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float fov;
    float aspect;
    float near;
    float far;
};

// Implementation of Camera methods

Camera::Camera(float fov, float aspect, float near, float far)
    : position(0.0f, 0.0f, 3.0f), front(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f),
      fov(fov), aspect(aspect), near(near), far(far) {}

void Camera::move(const glm::vec3& offset) {
    position += offset;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}