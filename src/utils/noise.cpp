#include "noise.h"
#include <cmath>
#include <cstdlib>

float generateNoise(float x, float y) {
    // Simplex noise or Perlin noise generation can be implemented here
    // For demonstration, we'll use a basic random function
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float interpolate(float a, float b, float t) {
    return a + t * (b - a);
}

float smoothNoise(float x, float y) {
    float corners = (generateNoise(x - 1, y - 1) + generateNoise(x + 1, y - 1) +
                     generateNoise(x - 1, y + 1) + generateNoise(x + 1, y + 1)) / 16.0;
    float sides = (generateNoise(x - 1, y) + generateNoise(x + 1, y) +
                   generateNoise(x, y - 1) + generateNoise(x, y + 1)) / 8.0;
    float center = generateNoise(x, y) / 4.0;
    return corners + sides + center;
}

float noise(float x, float y) {
    int integerX = static_cast<int>(x);
    int integerY = static_cast<int>(y);
    float fractionalX = x - integerX;
    float fractionalY = y - integerY;

    float v1 = smoothNoise(integerX, integerY);
    float v2 = smoothNoise(integerX + 1, integerY);
    float v3 = smoothNoise(integerX, integerY + 1);
    float v4 = smoothNoise(integerX + 1, integerY + 1);

    float i1 = interpolate(v1, v2, fractionalX);
    float i2 = interpolate(v3, v4, fractionalX);

    return interpolate(i1, i2, fractionalY);
}