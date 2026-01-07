#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"

class Camera;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void init();
    void render(Camera& camera);
    void cleanup();

private:
    Shader shader;
};

#endif // RENDERER_H