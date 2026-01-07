const express = require('express');
const path = require('path');
const os = require('os');

const app = express();
const PORT = process.env.PORT || 3000;

// Serve static files from the public directory
app.use(express.static(path.join(__dirname, 'public')));

// Main route
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

// Get server IP addresses
function getServerIPs() {
    const interfaces = os.networkInterfaces();
    const addresses = [];
    
    for (const name of Object.keys(interfaces)) {
        for (const iface of interfaces[name]) {
            // Skip internal and non-IPv4 addresses
            if (iface.family === 'IPv4' && !iface.internal) {
                addresses.push(iface.address);
            }
        }
    }
    
    return addresses;
}

// Start server
app.listen(PORT, '0.0.0.0', () => {
    const ips = getServerIPs();
    
    console.log('\n========================================');
    console.log('🎮 Minecraft Clone Server Started!');
    console.log('========================================\n');
    console.log(`Local:    http://localhost:${PORT}`);
    
    if (ips.length > 0) {
        console.log('\nNetwork Access:');
        ips.forEach(ip => {
            console.log(`          http://${ip}:${PORT}`);
        });
    }
    
    console.log('\n========================================');
    console.log('📝 Share the Network URL with others');
    console.log('   to play from different devices!');
    console.log('========================================\n');
});

// Handle errors
app.on('error', (err) => {
    console.error('Server error:', err);
});

process.on('uncaughtException', (err) => {
    console.error('Uncaught exception:', err);
});

process.on('unhandledRejection', (reason, promise) => {
    console.error('Unhandled rejection at:', promise, 'reason:', reason);
});
