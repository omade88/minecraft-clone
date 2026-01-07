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

## Complete Setup Guide - Start to Finish

This comprehensive guide walks you through setting up the Minecraft clone on a fresh Ubuntu installation.

### Phase 1: System Preparation

#### Step 1.1: Update System Packages
```bash
# Update package lists
sudo apt update

# Upgrade existing packages
sudo apt upgrade -y

# Install essential build tools (recommended)
sudo apt install -y build-essential curl wget
```

**Verification:**
```bash
# Check Ubuntu version
lsb_release -a
# Should show Ubuntu 18.04 or higher
```

#### Step 1.2: Install Git
```bash
# Install Git
sudo apt install -y git

# Configure Git (replace with your details)
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"
```

**Verification:**
```bash
git --version
# Should show: git version 2.x.x
```

### Phase 2: Install Node.js

#### Step 2.1: Install Node.js via NodeSource Repository
```bash
# Download and run NodeSource setup script for Node.js 20.x LTS
curl -fsSL https://deb.nodesource.com/setup_20.x | sudo -E bash -

# Install Node.js and npm
sudo apt install -y nodejs
```

**Verification:**
```bash
# Check Node.js version
node --version
# Should show: v20.x.x or higher

# Check npm version
npm --version
# Should show: 10.x.x or higher
```

#### Step 2.2: Alternative - Install via NVM (Node Version Manager)
If you prefer more flexibility with Node versions:
```bash
# Install NVM
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.7/install.sh | bash

# Reload shell configuration
source ~/.bashrc

# Install Node.js 20 LTS
nvm install 20

# Set default version
nvm use 20
nvm alias default 20
```

**Verification:**
```bash
nvm current
# Should show: v20.x.x
```

### Phase 3: Clone and Setup Project

#### Step 3.1: Create Project Directory
```bash
# Navigate to home directory
cd ~

# Create projects folder (optional but organized)
mkdir -p ~/projects
cd ~/projects
```

#### Step 3.2: Clone the Repository
```bash
# Clone from GitHub
git clone https://github.com/omade88/minecraft-clone.git

# Enter project directory
cd minecraft-clone

# Verify files are present
ls -la
```

**Expected Output:**
```
.gitignore
CMakeLists.txt
package.json
README.md
server.js
public/
src/
shaders/
```

#### Step 3.3: Install Project Dependencies
```bash
# Install npm packages
npm install

# This will create node_modules/ directory
```

**Verification:**
```bash
# Check if node_modules exists
ls -ld node_modules
# Should show the directory

# Check installed packages
npm list --depth=0
# Should show: express@^4.18.2
```

### Phase 4: Configure Firewall

#### Step 4.1: Check Firewall Status
```bash
# Check if UFW is active
sudo ufw status
```

#### Step 4.2: Allow Port 3000
```bash
# Allow incoming connections on port 3000
sudo ufw allow 3000/tcp

# Reload firewall
sudo ufw reload

# Verify rule was added
sudo ufw status numbered
```

**Expected Output:**
```
Status: active

     To                         Action      From
     --                         ------      ----
[ 1] 3000/tcp                   ALLOW IN    Anywhere
```

### Phase 5: Get Server IP Address

#### Step 5.1: Find Your IP Address
```bash
# Method 1: Using hostname
hostname -I

# Method 2: Using ip command
ip addr show | grep "inet " | grep -v 127.0.0.1

# Method 3: Using ifconfig (if installed)
ifconfig | grep "inet " | grep -v 127.0.0.1
```

**Note the IP address** (e.g., 192.168.1.100) - you'll need this to access the game from other devices.

#### Step 5.2: Test Network Connectivity
```bash
# Test if port 3000 is not already in use
sudo lsof -i :3000
# Should return nothing (port is free)

# If port is in use, find and kill the process:
# sudo kill -9 <PID>
```

### Phase 6: Start the Game Server

#### Step 6.1: First Run
```bash
# Make sure you're in the project directory
cd ~/projects/minecraft-clone

# Start the server
npm start
```

**Expected Output:**
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

**Keep this terminal open** - the server is now running!

#### Step 6.2: Verify Server is Running
Open a new terminal and run:
```bash
# Check if Node.js process is running
ps aux | grep node

# Test local connection
curl http://localhost:3000
# Should return HTML content
```

### Phase 7: Access and Test the Game

#### Step 7.1: Test on Local Machine (Ubuntu)
```bash
# If Ubuntu has a GUI, open browser
firefox http://localhost:3000
# OR
google-chrome http://localhost:3000
# OR
xdg-open http://localhost:3000
```

#### Step 7.2: Test from Another Device
1. **Get your Ubuntu server IP** (from Step 5.1)
2. **On another computer/phone**, open a web browser
3. **Navigate to:** `http://<ubuntu-ip>:3000`
   - Example: `http://192.168.1.100:3000`

#### Step 7.3: Verify Game Functionality
1. Click **"Click to Play"** button
2. Mouse should lock to the game window
3. Press **W** key - you should move forward
4. Move mouse - camera should rotate
5. **Left-click** on a block - it should disappear
6. **Right-click** on a block - new block should appear
7. Press **ESC** - mouse should unlock

**If everything works, setup is complete! ✅**

### Phase 8: Stopping the Server

#### Step 8.1: Stop Foreground Server
```bash
# In the terminal where server is running, press:
Ctrl + C

# Verify server stopped
curl http://localhost:3000
# Should show: "Connection refused" or timeout
```

### Troubleshooting During Setup

#### Issue: "Permission denied" during npm install
```bash
# Fix npm permissions
mkdir ~/.npm-global
npm config set prefix '~/.npm-global'
echo 'export PATH=~/.npm-global/bin:$PATH' >> ~/.bashrc
source ~/.bashrc
```

#### Issue: "Cannot find module 'express'"
```bash
# Reinstall dependencies
rm -rf node_modules package-lock.json
npm install
```

#### Issue: "Address already in use" on port 3000
```bash
# Find process using port 3000
sudo lsof -i :3000

# Kill the process (replace <PID> with actual process ID)
sudo kill -9 <PID>

# Or use a different port
PORT=8080 npm start
```

#### Issue: Can't access from other devices
```bash
# Check firewall
sudo ufw status

# Ensure both devices are on same network
# Verify server IP
hostname -I

# Test connectivity from other device
# On the other device, run: ping <ubuntu-ip>
```

---

## Automation Guide

Once you've verified the manual setup works, you can automate the server to run on boot and restart automatically.

### Automation Method 1: Using systemd (Recommended)

#### Step A1: Create systemd Service File
```bash
# Create service file
sudo nano /etc/systemd/system/minecraft-clone.service
```

**Add this content:**
```ini
[Unit]
Description=Minecraft Clone Browser Game
After=network.target

[Service]
Type=simple
User=YOUR_USERNAME
WorkingDirectory=/home/YOUR_USERNAME/projects/minecraft-clone
ExecStart=/usr/bin/node server.js
Restart=always
RestartSec=10
StandardOutput=syslog
StandardError=syslog
SyslogIdentifier=minecraft-clone
Environment=NODE_ENV=production
Environment=PORT=3000

[Install]
WantedBy=multi-user.target
```

**Replace:**
- `YOUR_USERNAME` with your actual Ubuntu username (run `whoami` to see it)
- Adjust `WorkingDirectory` path if you installed elsewhere

**Save and exit** (Ctrl+O, Enter, Ctrl+X)

#### Step A2: Enable and Start Service
```bash
# Reload systemd to recognize new service
sudo systemctl daemon-reload

# Enable service to start on boot
sudo systemctl enable minecraft-clone

# Start the service now
sudo systemctl start minecraft-clone

# Check service status
sudo systemctl status minecraft-clone
```

**Expected Output:**
```
● minecraft-clone.service - Minecraft Clone Browser Game
   Loaded: loaded (/etc/systemd/system/minecraft-clone.service; enabled)
   Active: active (running) since ...
```

#### Step A3: Manage the Service
```bash
# Check status
sudo systemctl status minecraft-clone

# Stop service
sudo systemctl stop minecraft-clone

# Restart service
sudo systemctl restart minecraft-clone

# View logs
sudo journalctl -u minecraft-clone -f

# Disable auto-start on boot
sudo systemctl disable minecraft-clone
```

### Automation Method 2: Using PM2 (Process Manager)

#### Step B1: Install PM2 Globally
```bash
# Install PM2
sudo npm install -g pm2

# Verify installation
pm2 --version
```

#### Step B2: Start Application with PM2
```bash
# Navigate to project directory
cd ~/projects/minecraft-clone

# Start with PM2
pm2 start server.js --name minecraft-clone

# View status
pm2 status
```

**Expected Output:**
```
┌─────┬────────────────────┬─────────┬─────────┬──────────┐
│ id  │ name               │ mode    │ ↺       │ status   │
├─────┼────────────────────┼─────────┼─────────┼──────────┤
│ 0   │ minecraft-clone    │ fork    │ 0       │ online   │
└─────┴────────────────────┴─────────┴─────────┴──────────┘
```

#### Step B3: Configure Auto-Start on Boot
```bash
# Save current PM2 process list
pm2 save

# Generate startup script
pm2 startup

# Copy and run the command it outputs
# Example: sudo env PATH=$PATH:/usr/bin pm2 startup systemd -u username --hp /home/username
```

#### Step B4: Manage with PM2
```bash
# View all processes
pm2 list

# Monitor in real-time
pm2 monit

# View logs
pm2 logs minecraft-clone

# Restart
pm2 restart minecraft-clone

# Stop
pm2 stop minecraft-clone

# Remove from PM2
pm2 delete minecraft-clone
```

### Automation Method 3: Using Screen (Simple Background Process)

#### Step C1: Install Screen
```bash
# Install screen if not present
sudo apt install -y screen
```

#### Step C2: Run in Screen Session
```bash
# Create new screen session
screen -S minecraft

# Navigate to project and start server
cd ~/projects/minecraft-clone
npm start

# Detach from screen: Press Ctrl+A then D

# Reattach to screen
screen -r minecraft

# List all screen sessions
screen -ls
```

#### Step C3: Auto-Start with Crontab
```bash
# Edit crontab
crontab -e

# Add this line to start on reboot
@reboot cd /home/YOUR_USERNAME/projects/minecraft-clone && screen -dmS minecraft npm start

# Save and exit
```

### Automated Deployment Script

Create a complete automation script for fresh installations:

#### Create deployment script:
```bash
# Create script file
nano ~/deploy-minecraft.sh
```

**Add this content:**
```bash
#!/bin/bash

set -e  # Exit on error

echo "========================================="
echo "Minecraft Clone - Automated Deployment"
echo "========================================="

# Variables
PROJECT_DIR="$HOME/projects/minecraft-clone"
SERVICE_NAME="minecraft-clone"

# Update system
echo "Step 1: Updating system..."
sudo apt update && sudo apt upgrade -y

# Install Node.js
echo "Step 2: Installing Node.js..."
if ! command -v node &> /dev/null; then
    curl -fsSL https://deb.nodesource.com/setup_20.x | sudo -E bash -
    sudo apt install -y nodejs
fi

echo "Node version: $(node --version)"
echo "npm version: $(npm --version)"

# Install Git
echo "Step 3: Installing Git..."
sudo apt install -y git

# Clone repository
echo "Step 4: Cloning repository..."
mkdir -p ~/projects
cd ~/projects
if [ -d "$PROJECT_DIR" ]; then
    echo "Project already exists. Pulling latest changes..."
    cd "$PROJECT_DIR"
    git pull
else
    git clone https://github.com/omade88/minecraft-clone.git
    cd minecraft-clone
fi

# Install dependencies
echo "Step 5: Installing npm dependencies..."
npm install

# Configure firewall
echo "Step 6: Configuring firewall..."
sudo ufw allow 3000/tcp
sudo ufw reload || true

# Create systemd service
echo "Step 7: Creating systemd service..."
sudo bash -c "cat > /etc/systemd/system/$SERVICE_NAME.service" << EOF
[Unit]
Description=Minecraft Clone Browser Game
After=network.target

[Service]
Type=simple
User=$USER
WorkingDirectory=$PROJECT_DIR
ExecStart=/usr/bin/node server.js
Restart=always
RestartSec=10
StandardOutput=syslog
StandardError=syslog
SyslogIdentifier=$SERVICE_NAME
Environment=NODE_ENV=production
Environment=PORT=3000

[Install]
WantedBy=multi-user.target
EOF

# Enable and start service
echo "Step 8: Starting service..."
sudo systemctl daemon-reload
sudo systemctl enable $SERVICE_NAME
sudo systemctl restart $SERVICE_NAME

# Get IP address
IP_ADDR=$(hostname -I | awk '{print $1}')

echo ""
echo "========================================="
echo "✅ Deployment Complete!"
echo "========================================="
echo ""
echo "Server is running at:"
echo "  Local:   http://localhost:3000"
echo "  Network: http://$IP_ADDR:3000"
echo ""
echo "Service management:"
echo "  Status:  sudo systemctl status $SERVICE_NAME"
echo "  Logs:    sudo journalctl -u $SERVICE_NAME -f"
echo "  Restart: sudo systemctl restart $SERVICE_NAME"
echo ""
echo "========================================="
```

**Make executable and run:**
```bash
# Make script executable
chmod +x ~/deploy-minecraft.sh

# Run deployment script
~/deploy-minecraft.sh
```

### Automated Updates Script

Create a script to update the game:

```bash
# Create update script
nano ~/update-minecraft.sh
```

**Add this content:**
```bash
#!/bin/bash

set -e

echo "Updating Minecraft Clone..."

cd ~/projects/minecraft-clone

# Stop service
sudo systemctl stop minecraft-clone

# Pull latest changes
git pull

# Install/update dependencies
npm install

# Restart service
sudo systemctl start minecraft-clone

echo "✅ Update complete!"
sudo systemctl status minecraft-clone
```

**Make executable:**
```bash
chmod +x ~/update-minecraft.sh
```

### Monitoring and Logs

#### View Real-time Logs
```bash
# Using systemd
sudo journalctl -u minecraft-clone -f

# Using PM2
pm2 logs minecraft-clone --lines 100
```

#### Check Server Health
```bash
# Create health check script
cat > ~/check-minecraft.sh << 'EOF'
#!/bin/bash
RESPONSE=$(curl -s -o /dev/null -w "%{http_code}" http://localhost:3000)
if [ $RESPONSE -eq 200 ]; then
    echo "✅ Server is running"
else
    echo "❌ Server is down (HTTP $RESPONSE)"
fi
EOF

chmod +x ~/check-minecraft.sh
./check-minecraft.sh
```

### Backup Script

Automate backups:
```bash
# Create backup script
nano ~/backup-minecraft.sh
```

**Add this content:**
```bash
#!/bin/bash

BACKUP_DIR="$HOME/minecraft-backups"
PROJECT_DIR="$HOME/projects/minecraft-clone"
DATE=$(date +%Y%m%d_%H%M%S)

mkdir -p "$BACKUP_DIR"

tar -czf "$BACKUP_DIR/minecraft-clone-$DATE.tar.gz" \
    -C "$PROJECT_DIR" \
    --exclude='node_modules' \
    --exclude='build' \
    .

echo "✅ Backup created: $BACKUP_DIR/minecraft-clone-$DATE.tar.gz"

# Keep only last 5 backups
cd "$BACKUP_DIR"
ls -t minecraft-clone-*.tar.gz | tail -n +6 | xargs -r rm

echo "✅ Old backups cleaned"
```

**Make executable and schedule:**
```bash
chmod +x ~/backup-minecraft.sh

# Add to crontab for daily backups at 2 AM
crontab -e
# Add: 0 2 * * * /home/YOUR_USERNAME/backup-minecraft.sh
```

---

## Quick Reference Commands

### Essential Commands
```bash
# Start server manually
npm start

# Start server (systemd)
sudo systemctl start minecraft-clone

# Stop server (systemd)
sudo systemctl stop minecraft-clone

# View logs
sudo journalctl -u minecraft-clone -f

# Check server status
sudo systemctl status minecraft-clone

# Restart after changes
sudo systemctl restart minecraft-clone
```

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
# Install Node.js 20.x (LTS)
curl -fsSL https://deb.nodesource.com/setup_20.x | sudo -E bash -
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
nvm install 20
nvm use 20
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