#include "camera.h"

Camera::Camera(float fov, float aspect, float near, float far)
    : position(0.0f, 0.0f, 3.0f), front(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f),
      fov(fov), aspect(aspect), near(near), far(far) {}

void Camera::move(const glm::vec3& offset) {
    position += offset;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}