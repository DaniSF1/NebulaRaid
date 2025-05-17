# Nebula Raid (WIP)

**Nebula Raid** is a C++ arcade-style shooter built from scratch using [raylib](https://www.raylib.com/). The project is designed to showcase solid game architecture and programming principles, with a strong focus on performance, reusability, and scalability.

## 🧠 Architecture and Design Patterns

This project demonstrates the use of several design patterns and game development techniques:

### 🎮 State Pattern
Used to manage different game states (`MenuState`, `GameState`, `GameOverState`, etc.), enabling a clean and modular flow between scenes.

### ♻️ Object Pool Pattern
Bullets are managed via a custom generic `ObjectPool<T>`, avoiding costly dynamic allocations at runtime. Bullets are reused after being deactivated, minimizing memory fragmentation and boosting performance.

### 🧱 Strategy Pattern
Enemy behaviors (movement and attack) are decoupled into separate classes implementing `IMovementBehavior` and `IAttackBehavior`. This allows flexible combinations of behaviors across enemy types and promotes scalability.

### 🌐 Spatial Grid System
A grid-based system is used to optimize collision detection. Only nearby objects are checked, drastically reducing the number of comparisons per frame.

### 🧩 Factory Pattern
Enemies are instantiated via an `EnemyFactory`, which reads from a centralized JSON configuration. This system allows for quick prototyping and extension of new enemy types without touching gameplay code.

## ⚙️ Efficiency and Performance
- **Pooling** of bullets and reuse of enemy textures prevents memory bloat and redundant loading.
- **Separation of update/draw logic**, with only active entities processed each frame.
- **Controlled spawning** using JSON-based wave definitions.
- **Profiling tools** were used (e.g., logging tick frequency) to trace unexpected behavior, ensuring stability in enemy patterns and bullet flow.

## 📦 Tools and Technologies

- **C++**
- **[raylib](https://www.raylib.com/)**: lightweight C library for game development.
- **nlohmann/json** for JSON parsing.

## 🎮 Gameplay Overview

The player must dodge incoming projectiles and defeat enemies with various attack and movement patterns. Enemies are introduced via timed waves defined in JSON. Each enemy can behave uniquely thanks to behavior composition.

## 🛠️ Future Work
This project is still in development. Planned improvements include:
- Improved UI and menu aesthetics
- Endless mode with scaling difficulty

Stay tuned for updates as the project evolves!

Disclaimer: None of the sounds, sprites or art used in the game are mine. All assets used in the project are open source or are used with the permission of the author.
