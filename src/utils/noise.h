#ifndef NOISE_H
#define NOISE_H

// Function declarations for noise generation
float generatePerlinNoise(float x, float y);
float generateSimplexNoise(float x, float y);
void generateNoiseMap(float* noiseMap, int width, int height, float scale);

#endif // NOISE_H