#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(float fov = 45.0f, float aspect = 16.0f/9.0f, float near = 0.1f, float far = 100.0f);
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

#endif // CAMERA_H