# Minecraft Clone

## Overview
This project is a local Minecraft-like game designed to run on Ubuntu. It features a voxel-based world where players can explore, build, and interact with various elements.

## Project Structure
The project is organized into several directories and files:

- **src/**: Contains the source code for the game.
  - **main.cpp**: Entry point of the game.
  - **engine/**: Contains the game engine components.
    - **renderer.cpp**: Implementation of the rendering engine.
    - **renderer.h**: Header file for the rendering engine.
    - **camera.cpp**: Implementation of the camera system.
    - **camera.h**: Header file for the camera system.
    - **shader.cpp**: Implementation of the shader management.
    - **shader.h**: Header file for shader management.
  - **world/**: Contains the world generation and management code.
    - **chunk.cpp**: Implementation of the chunk system.
    - **chunk.h**: Header file for the chunk system.
    - **block.cpp**: Implementation of individual blocks.
    - **block.h**: Header file for block management.
    - **world.cpp**: Implementation of the overall world management.
    - **world.h**: Header file for world management.
  - **player/**: Contains player-related code.
    - **player.cpp**: Implementation of player controls and movement.
    - **player.h**: Header file for player management.
  - **utils/**: Contains utility functions.
    - **noise.cpp**: Implementation of noise generation for terrain.
    - **noise.h**: Header file for noise generation functions.
  
- **shaders/**: Contains shader files for rendering.
  - **vertex.glsl**: Vertex shader code.
  - **fragment.glsl**: Fragment shader code.

- **assets/**: Contains game assets such as textures.
  - **textures/**: Directory for texture files.

- **CMakeLists.txt**: Configuration file for building the project with CMake.

- **README.md**: Documentation for the project.

## Prerequisites

Before building and running this Minecraft clone, ensure you have the following dependencies installed on your Ubuntu system:

### Required Dependencies
- **GCC/G++** (version 7.0 or higher)
- **CMake** (version 3.10 or higher)
- **OpenGL** development libraries
- **GLFW3** (for window management and input)
- **GLEW** (OpenGL Extension Wrangler Library)
- **GLM** (OpenGL Mathematics library)
- **Git** (for version control)

## Step-by-Step Setup Instructions

### Step 1: Update Your System
First, update your package lists to ensure you get the latest versions:
```bash
sudo apt update
sudo apt upgrade -y
```

### Step 2: Install Build Tools
Install the essential build tools (GCC, G++, Make, CMake):
```bash
sudo apt install -y build-essential cmake git
```

### Step 3: Install OpenGL and Graphics Libraries
Install the required OpenGL and graphics development libraries:
```bash
sudo apt install -y libgl1-mesa-dev libglu1-mesa-dev
```

### Step 4: Install GLFW3
Install GLFW3 for window creation and input handling:
```bash
sudo apt install -y libglfw3-dev
```

### Step 5: Install GLEW
Install GLEW for managing OpenGL extensions:
```bash
sudo apt install -y libglew-dev
```

### Step 6: Install GLM
Install GLM for mathematics operations:
```bash
sudo apt install -y libglm-dev
```

### Step 7: Verify Installation
Verify that all tools are properly installed:
```bash
gcc --version
g++ --version
cmake --version
pkg-config --modversion glfw3
```

### Step 8: Clone the Repository
Clone this repository to your local machine:
```bash
git clone <repository-url>
cd minecraft-clone
```

### Step 9: Create Build Directory
Create a separate directory for building the project (out-of-source build):
```bash
mkdir build
cd build
```

### Step 10: Configure with CMake
Run CMake to configure the project and generate build files:
```bash
cmake ..
```

If you encounter any errors, make sure all dependencies are properly installed. You can specify a build type for optimization:
```bash
# For debug build (with debugging symbols)
cmake -DCMAKE_BUILD_TYPE=Debug ..

# For release build (optimized)
cmake -DCMAKE_BUILD_TYPE=Release ..
```

### Step 11: Build the Project
Compile the project using make:
```bash
make
```

For faster compilation on multi-core systems, use parallel jobs:
```bash
make -j$(nproc)
```

### Step 12: Run the Game
Once the build is complete, run the executable:
```bash
./minecraft-clone
```

Or from the project root directory:
```bash
./build/minecraft-clone
```

## Troubleshooting

### Common Issues and Solutions

#### Issue: "CMake not found"
**Solution:** Install CMake using `sudo apt install cmake`

#### Issue: "GLFW3 not found"
**Solution:** Ensure GLFW3 is installed: `sudo apt install libglfw3-dev`

#### Issue: "OpenGL headers not found"
**Solution:** Install Mesa development libraries: `sudo apt install libgl1-mesa-dev libglu1-mesa-dev`

#### Issue: "Permission denied" when running the executable
**Solution:** Make the file executable: `chmod +x ./build/minecraft-clone`

#### Issue: Graphics driver issues
**Solution:** Update your graphics drivers:
```bash
# For NVIDIA
sudo ubuntu-drivers autoinstall

# For AMD
sudo apt install mesa-vulkan-drivers mesa-utils
```

#### Issue: Black screen or rendering problems
**Solution:** 
- Verify OpenGL support: `glxinfo | grep "OpenGL version"`
- Update graphics drivers
- Try running in software rendering mode (slower): `LIBGL_ALWAYS_SOFTWARE=1 ./build/minecraft-clone`

## Running the Game

### Controls
(Customize this section based on your actual implementation)
- **W/A/S/D**: Move forward/left/backward/right
- **Space**: Jump
- **Mouse**: Look around
- **Left Click**: Break block
- **Right Click**: Place block
- **ESC**: Pause/Exit

### Performance Optimization
For better performance, you can:
1. Build in Release mode: `cmake -DCMAKE_BUILD_TYPE=Release ..`
2. Reduce render distance in game settings
3. Ensure you have proper graphics drivers installed

## Development Workflow

### Making Changes
1. Edit source files in the `src/` directory
2. Rebuild the project: `cd build && make`
3. Run and test: `./minecraft-clone`

### Clean Build
If you need to start fresh:
```bash
cd build
rm -rf *
cmake ..
make
```

Or simply:
```bash
rm -rf build
mkdir build
cd build
cmake ..
make
```

## Gameplay
In this game, players can explore a procedurally generated world, gather resources, and build structures. The game features a simple user interface and basic controls for movement and interaction.

## Contributing
Contributions are welcome! Please feel free to submit a pull request or open an issue for any suggestions or improvements.