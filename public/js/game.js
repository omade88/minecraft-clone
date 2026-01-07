// Minecraft Clone - Browser Edition
// Main Game Logic

class MinecraftGame {
    constructor() {
        this.scene = null;
        this.camera = null;
        this.renderer = null;
        this.controls = {
            forward: false,
            backward: false,
            left: false,
            right: false,
            jump: false
        };
        this.player = {
            position: new THREE.Vector3(0, 20, 0),
            velocity: new THREE.Vector3(0, 0, 0),
            rotation: new THREE.Euler(0, 0, 0),
            speed: 0.1,
            jumpForce: 0.3,
            onGround: false
        };
        this.mouseMovement = { x: 0, y: 0 };
        this.blocks = [];
        this.raycaster = new THREE.Raycaster();
        this.mouse = new THREE.Vector2();
        this.isLocked = false;
        this.lastTime = performance.now();
        this.fps = 0;
        this.frameCount = 0;
        this.fpsTime = 0;
    }

    init() {
        // Setup Scene
        this.scene = new THREE.Scene();
        this.scene.background = new THREE.Color(0x87CEEB);
        this.scene.fog = new THREE.Fog(0x87CEEB, 0, 100);

        // Setup Camera
        this.camera = new THREE.PerspectiveCamera(
            75,
            window.innerWidth / window.innerHeight,
            0.1,
            1000
        );
        this.camera.position.copy(this.player.position);

        // Setup Renderer
        const canvas = document.getElementById('game-canvas');
        this.renderer = new THREE.WebGLRenderer({ canvas, antialias: true });
        this.renderer.setSize(window.innerWidth, window.innerHeight);
        this.renderer.shadowMap.enabled = true;

        // Add Lighting
        const ambientLight = new THREE.AmbientLight(0xffffff, 0.6);
        this.scene.add(ambientLight);

        const directionalLight = new THREE.DirectionalLight(0xffffff, 0.8);
        directionalLight.position.set(50, 100, 50);
        directionalLight.castShadow = true;
        directionalLight.shadow.camera.left = -50;
        directionalLight.shadow.camera.right = 50;
        directionalLight.shadow.camera.top = 50;
        directionalLight.shadow.camera.bottom = -50;
        this.scene.add(directionalLight);

        // Generate World
        this.generateWorld();

        // Setup Event Listeners
        this.setupEventListeners();

        // Hide loading screen
        document.getElementById('loading').style.display = 'none';
        document.getElementById('start-screen').style.display = 'flex';

        // Start game loop
        this.animate();
    }

    generateWorld() {
        const blockSize = 1;
        const worldSize = 20;
        
        // Create block materials
        const grassMaterial = new THREE.MeshLambertMaterial({ color: 0x567d46 });
        const dirtMaterial = new THREE.MeshLambertMaterial({ color: 0x8B4513 });
        const stoneMaterial = new THREE.MeshLambertMaterial({ color: 0x808080 });
        
        const geometry = new THREE.BoxGeometry(blockSize, blockSize, blockSize);

        // Generate terrain
        for (let x = -worldSize; x < worldSize; x++) {
            for (let z = -worldSize; z < worldSize; z++) {
                // Simple noise-like height variation
                const height = Math.floor(
                    Math.sin(x * 0.1) * Math.cos(z * 0.1) * 3 + 5
                );

                for (let y = 0; y < height; y++) {
                    let material;
                    if (y === height - 1) {
                        material = grassMaterial;
                    } else if (y >= height - 4) {
                        material = dirtMaterial;
                    } else {
                        material = stoneMaterial;
                    }

                    const block = new THREE.Mesh(geometry, material);
                    block.position.set(x, y, z);
                    block.castShadow = true;
                    block.receiveShadow = true;
                    block.userData = { type: 'block', breakable: true };
                    this.scene.add(block);
                    this.blocks.push(block);
                }
            }
        }

        this.updateBlockCount();
    }

    setupEventListeners() {
        // Keyboard events
        document.addEventListener('keydown', (e) => this.onKeyDown(e));
        document.addEventListener('keyup', (e) => this.onKeyUp(e));

        // Mouse events
        document.addEventListener('mousemove', (e) => this.onMouseMove(e));
        document.addEventListener('mousedown', (e) => this.onMouseDown(e));

        // Pointer lock
        const startButton = document.getElementById('start-button');
        startButton.addEventListener('click', () => {
            document.body.requestPointerLock();
        });

        document.addEventListener('pointerlockchange', () => {
            this.isLocked = document.pointerLockElement === document.body;
            if (this.isLocked) {
                document.getElementById('start-screen').style.display = 'none';
            }
        });

        // Window resize
        window.addEventListener('resize', () => this.onWindowResize());
    }

    onKeyDown(event) {
        switch (event.code) {
            case 'KeyW': this.controls.forward = true; break;
            case 'KeyS': this.controls.backward = true; break;
            case 'KeyA': this.controls.left = true; break;
            case 'KeyD': this.controls.right = true; break;
            case 'Space': this.controls.jump = true; break;
        }
    }

    onKeyUp(event) {
        switch (event.code) {
            case 'KeyW': this.controls.forward = false; break;
            case 'KeyS': this.controls.backward = false; break;
            case 'KeyA': this.controls.left = false; break;
            case 'KeyD': this.controls.right = false; break;
            case 'Space': this.controls.jump = false; break;
        }
    }

    onMouseMove(event) {
        if (!this.isLocked) return;

        const sensitivity = 0.002;
        this.player.rotation.y -= event.movementX * sensitivity;
        this.player.rotation.x -= event.movementY * sensitivity;
        
        // Limit vertical rotation
        this.player.rotation.x = Math.max(
            -Math.PI / 2,
            Math.min(Math.PI / 2, this.player.rotation.x)
        );
    }

    onMouseDown(event) {
        if (!this.isLocked) return;

        this.raycaster.setFromCamera(new THREE.Vector2(0, 0), this.camera);
        const intersects = this.raycaster.intersectObjects(this.blocks);

        if (intersects.length > 0) {
            const intersect = intersects[0];
            
            if (event.button === 0) {
                // Left click - break block
                this.breakBlock(intersect.object);
            } else if (event.button === 2) {
                // Right click - place block
                this.placeBlock(intersect);
            }
        }
    }

    breakBlock(block) {
        if (block.userData.breakable) {
            this.scene.remove(block);
            const index = this.blocks.indexOf(block);
            if (index > -1) {
                this.blocks.splice(index, 1);
            }
            this.updateBlockCount();
        }
    }

    placeBlock(intersect) {
        const geometry = new THREE.BoxGeometry(1, 1, 1);
        const material = new THREE.MeshLambertMaterial({ color: 0x567d46 });
        const block = new THREE.Mesh(geometry, material);
        
        // Calculate position based on face normal
        const position = intersect.point.add(intersect.face.normal);
        block.position.set(
            Math.floor(position.x),
            Math.floor(position.y),
            Math.floor(position.z)
        );
        
        block.castShadow = true;
        block.receiveShadow = true;
        block.userData = { type: 'block', breakable: true };
        
        this.scene.add(block);
        this.blocks.push(block);
        this.updateBlockCount();
    }

    updatePlayer() {
        // Apply gravity
        this.player.velocity.y -= 0.01;

        // Movement
        const forward = new THREE.Vector3(0, 0, -1);
        const right = new THREE.Vector3(1, 0, 0);
        
        forward.applyEuler(new THREE.Euler(0, this.player.rotation.y, 0));
        right.applyEuler(new THREE.Euler(0, this.player.rotation.y, 0));

        if (this.controls.forward) {
            this.player.velocity.add(forward.multiplyScalar(this.player.speed));
        }
        if (this.controls.backward) {
            this.player.velocity.add(forward.multiplyScalar(-this.player.speed));
        }
        if (this.controls.left) {
            this.player.velocity.add(right.multiplyScalar(-this.player.speed));
        }
        if (this.controls.right) {
            this.player.velocity.add(right.multiplyScalar(this.player.speed));
        }
        if (this.controls.jump && this.player.onGround) {
            this.player.velocity.y = this.player.jumpForce;
        }

        // Update position
        this.player.position.add(this.player.velocity);

        // Simple ground collision
        if (this.player.position.y < 10) {
            this.player.position.y = 10;
            this.player.velocity.y = 0;
            this.player.onGround = true;
        } else {
            this.player.onGround = false;
        }

        // Apply friction
        this.player.velocity.x *= 0.8;
        this.player.velocity.z *= 0.8;

        // Update camera
        this.camera.position.copy(this.player.position);
        this.camera.rotation.set(
            this.player.rotation.x,
            this.player.rotation.y,
            this.player.rotation.z
        );

        this.updateHUD();
    }

    updateHUD() {
        const pos = this.player.position;
        document.getElementById('position').textContent = 
            `${pos.x.toFixed(1)}, ${pos.y.toFixed(1)}, ${pos.z.toFixed(1)}`;
    }

    updateBlockCount() {
        document.getElementById('blocks').textContent = this.blocks.length;
    }

    updateFPS() {
        this.frameCount++;
        const currentTime = performance.now();
        const deltaTime = currentTime - this.fpsTime;

        if (deltaTime >= 1000) {
            this.fps = Math.round((this.frameCount * 1000) / deltaTime);
            document.getElementById('fps').textContent = this.fps;
            this.frameCount = 0;
            this.fpsTime = currentTime;
        }
    }

    onWindowResize() {
        this.camera.aspect = window.innerWidth / window.innerHeight;
        this.camera.updateProjectionMatrix();
        this.renderer.setSize(window.innerWidth, window.innerHeight);
    }

    animate() {
        requestAnimationFrame(() => this.animate());

        if (this.isLocked) {
            this.updatePlayer();
        }

        this.updateFPS();
        this.renderer.render(this.scene, this.camera);
    }
}

// Initialize game when page loads
window.addEventListener('DOMContentLoaded', () => {
    const game = new MinecraftGame();
    game.init();
});

// Prevent context menu on right click
window.addEventListener('contextmenu', (e) => e.preventDefault());
