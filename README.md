# Minecraft Clone - Browser Edition

## Overview
This is a browser-based Minecraft-like game built with Three.js and WebGL. The game runs on an Ubuntu server and can be accessed from any web browser via IP address. Players can explore a procedurally generated voxel world, break and place blocks, and enjoy a 3D gaming experience directly in their browser.

## Features
- 🎮 **Browser-based gameplay** - No installation required, play directly in your browser
- 🌍 **Procedurally generated terrain** - Dynamic world generation with varied heights
- 🧱 **Block building mechanics** - Break and place blocks like classic Minecraft
- 🎯 **First-person controls** - WASD movement with mouse look
- 📊 **Real-time HUD** - FPS counter, position tracker, and block count
- 🌐 **Network accessible** - Play from any device on your network

## Project Structure
The project is organized into the following directories and files:

- **public/**: Client-side web application
  - **index.html**: Main game interface with HUD and controls
  - **js/game.js**: Three.js game logic, rendering, and player controls
  
- **server.js**: Node.js/Express server to host the game

- **package.json**: Node.js dependencies and scripts

- **src/**: Legacy C++ implementation (not used for browser version)

- **CMakeLists.txt**: Build configuration (legacy, not used for browser version)

- **.gitignore**: Git ignore rules

- **README.md**: This documentation file

## Prerequisites

To run this browser-based Minecraft clone on Ubuntu, you need:

### Required Software
- **Node.js** (version 14.0 or higher)
- **npm** (comes with Node.js)
- **Git** (for version control)

## Step-by-Step Setup Instructions

### Step 1: Update Your System
First, update your package lists:
```bash
sudo apt update
sudo apt upgrade -y
```

### Step 2: Install Node.js and npm
Install Node.js (version 14 or higher):
```bash
# Install Node.js 18.x (LTS)
curl -fsSL https://deb.nodesource.com/setup_18.x | sudo -E bash -
sudo apt install -y nodejs

# Verify installation
node --version
npm --version
```

Alternative method using nvm (Node Version Manager):
```bash
# Install nvm
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.0/install.sh | bash
source ~/.bashrc

# Install Node.js
nvm install 18
nvm use 18
```

### Step 3: Clone the Repository
Clone this repository to your Ubuntu machine:
```bash
git clone https://github.com/omade88/minecraft-clone.git
cd minecraft-clone
```

### Step 4: Install Dependencies
Install the required npm packages:
```bash
npm install
```

This will install:
- **Express**: Web server framework
- **Nodemon**: Auto-restart server during development (optional)

### Step 5: Start the Server
Run the game server:
```bash
npm start
```

The server will display output like:
```
========================================
🎮 Minecraft Clone Server Started!
========================================

Local:    http://localhost:3000

Network Access:
          http://192.168.1.100:3000

========================================
📝 Share the Network URL with others
   to play from different devices!
========================================
```

### Step 6: Access the Game
Open a web browser and navigate to one of the URLs shown:

**On the same Ubuntu machine:**
- Visit `http://localhost:3000`

**From another device on the same network:**
- Visit `http://<your-ubuntu-ip>:3000`
- Replace `<your-ubuntu-ip>` with the IP shown in the server output

### Step 7: Find Your Server IP (if needed)
If you need to find your Ubuntu server's IP address:
```bash
# Show all network interfaces
ip addr show

# Or use hostname command
hostname -I

# Or use ifconfig (if installed)
ifconfig
```

Look for the IP address under your active network interface (usually `eth0` for Ethernet or `wlan0` for WiFi).

### Step 8: Configure Firewall (if needed)
If you can't access the game from other devices, you may need to allow traffic on port 3000:
```bash
# For ufw firewall
sudo ufw allow 3000/tcp
sudo ufw status

# For iptables
sudo iptables -A INPUT -p tcp --dport 3000 -j ACCEPT
```

### Step 9: Start Playing!
1. Click **"Click to Play"** button
2. The mouse will lock to the game window
3. Use the controls to move around and build

## Running the Game

### Game Controls
- **W/A/S/D**: Move forward/left/backward/right
- **Space**: Jump
- **Mouse**: Look around (after clicking "Click to Play")
- **Left Click**: Break block (remove)
- **Right Click**: Place block
- **ESC**: Unlock mouse pointer

### Starting the Server

**Production Mode:**
```bash
npm start
```

**Development Mode (auto-restart on code changes):**
```bash
npm run dev
```

**Custom Port:**
```bash
PORT=8080 npm start
```

### Accessing from Different Devices

**Same Computer:**
- `http://localhost:3000`

**Other Computers/Phones on Same WiFi:**
- `http://<ubuntu-server-ip>:3000`

**Over the Internet (requires port forwarding):**
- Configure your router to forward port 3000 to your Ubuntu machine
- Access via `http://<your-public-ip>:3000`

### Performance Tips
- Use a modern browser (Chrome, Firefox, Edge)
- Ensure hardware acceleration is enabled in browser settings
- Close other tabs to free up GPU resources
- Lower quality settings if experiencing lag

## Troubleshooting

### Common Issues and Solutions

#### Issue: "Cannot GET /" or blank page
**Solution:** Ensure the server is running and you're using the correct URL
```bash
# Check if server is running
ps aux | grep node

# Restart the server
npm start
```

#### Issue: Can't access from another device
**Solution:** 
1. Check firewall settings:
```bash
sudo ufw allow 3000/tcp
sudo ufw reload
```

2. Verify server is listening on all interfaces (0.0.0.0)
3. Confirm both devices are on the same network
4. Get your Ubuntu IP:
```bash
hostname -I
```

#### Issue: "npm: command not found"
**Solution:** Install Node.js and npm:
```bash
curl -fsSL https://deb.nodesource.com/setup_18.x | sudo -E bash -
sudo apt install -y nodejs
```

#### Issue: "Port 3000 is already in use"
**Solution:** Either stop the other process or use a different port:
```bash
# Find what's using port 3000
sudo lsof -i :3000

# Use a different port
PORT=8080 npm start
```

#### Issue: Game is laggy or slow
**Solution:** 
- Close other browser tabs
- Check browser console for errors (F12)
- Ensure you have a good GPU
- Try a different browser (Chrome recommended)
- Reduce window size

#### Issue: Mouse won't lock / pointer lock not working
**Solution:** 
- Click the "Click to Play" button
- Some browsers require user interaction first
- Try pressing ESC and clicking again
- Check browser permissions for pointer lock

#### Issue: Blocks not appearing or rendering issues
**Solution:**
- Clear browser cache
- Hard refresh (Ctrl+Shift+R or Cmd+Shift+R)
- Check browser console for errors
- Ensure WebGL is supported: visit `chrome://gpu/`

### Server Management

**Run server in background:**
```bash
# Using nohup
nohup npm start &

# Using screen
screen -S minecraft
npm start
# Press Ctrl+A then D to detach
# Reattach with: screen -r minecraft

# Using pm2 (recommended for production)
sudo npm install -g pm2
pm2 start server.js --name minecraft-clone
pm2 save
pm2 startup
```

**Stop background server:**
```bash
# If using pm2
pm2 stop minecraft-clone

# Find and kill process
ps aux | grep node
kill <process-id>
```

## Development Workflow

### Making Changes to the Game

**1. Modify game logic:**
Edit `public/js/game.js`

**2. Update UI/styling:**
Edit `public/index.html`

**3. Change server behavior:**
Edit `server.js`

**4. Test changes:**
```bash
# Use nodemon for auto-reload
npm run dev
```

**5. Refresh browser:**
Hard refresh (Ctrl+Shift+R) to see changes

### Adding New Features

To add block types, modify `public/js/game.js`:
```javascript
// Add in generateWorld() or placeBlock() method
const newMaterial = new THREE.MeshLambertMaterial({ color: 0xFF0000 });
```

To change world generation, edit the `generateWorld()` method in `public/js/game.js`

## Advanced Configuration

### Running on a Different Port

Edit `server.js` or use environment variable:
```bash
PORT=8080 npm start
```

### Enabling HTTPS (for remote access)

For secure connections, set up an nginx reverse proxy with SSL:
```bash
sudo apt install nginx certbot
# Configure nginx and obtain SSL certificate
```

### Network Performance Optimization

For better performance over network:
1. Use a wired connection instead of WiFi
2. Ensure good signal strength if using WiFi
3. Close bandwidth-heavy applications
4. Consider using a CDN for Three.js library (already configured)

## Technology Stack

- **Frontend**: Three.js (WebGL), HTML5, CSS3, JavaScript
- **Backend**: Node.js, Express
- **3D Graphics**: Three.js r128
- **Server**: Express.js web server

## Browser Compatibility

This game works best on modern browsers with WebGL support:
- ✅ Chrome/Chromium (recommended)
- ✅ Firefox
- ✅ Edge
- ✅ Safari (macOS/iOS)
- ✅ Opera

**Minimum Requirements:**
- WebGL-capable browser
- Mouse and keyboard
- Stable internet connection (for CDN resources)

## Future Enhancements

Potential features to add:
- Multiplayer support with WebSockets
- More block types and textures
- Inventory system
- Day/night cycle
- Mob spawning
- Save/load world state
- Touch controls for mobile devices
- Improved terrain generation with Perlin noise

## Gameplay
Players can explore a procedurally generated voxel world directly in their web browser. Use WASD keys to move around, the mouse to look, left-click to break blocks, and right-click to place new blocks. The game features real-time rendering with Three.js and provides an immersive first-person experience similar to Minecraft.

## Contributing
Contributions are welcome! Please feel free to submit a pull request or open an issue for any suggestions or improvements.