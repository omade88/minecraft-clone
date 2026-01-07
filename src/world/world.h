#ifndef WORLD_H
#define WORLD_H

#include <vector>

class Chunk;

class World {
public:
    World();
    ~World();
    
    void load();
    void update();
    
private:
    std::vector<Chunk> chunks;
    void generateChunks();
};

#endif // WORLD_H