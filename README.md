# 🚀 Bullet Hell

**Vertical arcade shooter made in C++ using raylib.**  
Developed as a personal project to showcase knowledge in software architecture, performance optimization, and design patterns.

---

## 📌 Technical Features

### 🧱 Architecture
- **C++** with **Raylib**.
- Implements multiple **design patterns**:
  - `State`: for managing game states (e.g., `LevelState`, `GameOverState`).
  - `Strategy`: for modular enemy movement and attack behaviors.
  - `Factory`: to instantiate enemies based on external JSON definitions.
  - `Singleton`: `GameWorld` provides global access to the player.
  - `Object Pool`: for efficient bullet management and memory reuse.

---

### 🎮 Gameplay
- Enemies with modular AI (movement and attack are decoupled).
- **4 enemy types**:
  - `Basic`: random movement, simple shooting.
  - `Sniper`: shoots directly at the player.
  - `Turret`: fires bullets in circular patterns.
  - `Berserker`: changes movement and attack patterns based on remaining health.

---

### 📄 Level System
- Loads levels from **JSON** configuration:
  ```json
  {
    "backgroundTexture": "assets/bg.png",
    "musicTrack": "",
    "enemyWaves": [
      {
        "enemyType": "basic",
        "count": 10,
        "spawnDelay": 1.5,
        "startTime": 0
      }
    ]
  }
  ```
- Fully customizable enemy waves and spawn timing.
- Animated scrolling background and texture reuse.

---

### 🔫 Shooting System
- Each entity (`Player`, `Enemy`) has its own `Pool<Bullet>`.
- Bullets are recycled when leaving the screen or on collision.
- Bullet IDs and tracing for debugging movement issues.

---

### 🧠 Performance
- Shared static textures for all enemy instances.
- Bullet pooling for low-overhead reuse.
- Optimized spatial collision detection using a **Spatial Grid**.

---

### 🛠️ Tools & Libraries
- **raylib**: handles graphics, input, and audio.
- **nlohmann::json**: used for parsing level and enemy data.

---

> Built as part of a portfolio to demonstrate game programming and system design skills.
