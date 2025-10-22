# Development Setup

## Prerequisites
- C++ compiler (g++ or clang++)
- SFML 2.5 or higher
- Make

### Installing SFML

**Ubuntu/Debian:**
```bash
sudo apt-get install libsfml-dev
```

**macOS (Homebrew):**
```bash
brew install sfml
```

**Windows:**
Download from https://www.sfml-dev.org/download.php

## Building
```bash
# Compile the project
make

# Run the game
make run

# Clean build files
make clean
```

## Project Structure
```
src/        - Source files (.cpp)
includes/   - Header files (.h)
assets/     - Game assets (sprites, sounds, music)
obj/        - Compiled object files (auto-generated)
bin/        - Executable (auto-generated)
```

## Team Assignments
- **Person A:** Game loop, state management, UI
- **Person B:** Player, bullets, collision detection
- **Person C:** Centipede AI, mushrooms, assets