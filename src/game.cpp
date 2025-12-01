/**
 * @file game.cpp
 * @author Ian Codding II
 * @brief Implementation of Game class
 * @version 1.0 - Complete Integration
 * @date 2025-11-26
 *
 * @copyright Copyright (c) 2025
 */

#include "../includes/game.h"
#include "../includes/errorHandler.h"
#include <iostream>
#include <cstdlib>

/**
 * @brief Constructor - create the game
 */
Game::Game(sf::RenderWindow& win, ScreenManager& screenMngr)
    : window(win),
      screenManager(screenMngr),
      currentState(GameState::PLAYING),
      isGameOver(false),
      isPaused(false),
      grid(nullptr),
      collisionManager(nullptr),
      player(nullptr),
      score(0),
      lives(3),
      level(1) {

    std::cout << "[Game] Constructor called" << std::endl;

    // Get font from ScreenManager
    sf::Font& font = screenManager.getFont();

    // Set up background
    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color::Black);

    // Set up text displays
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::Green);
    scoreText.setPosition(10, 10);

    livesText.setFont(font);
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::Green);
    livesText.setPosition(window.getSize().x - 200, 10);

    levelText.setFont(font);
    levelText.setCharacterSize(20);
    levelText.setFillColor(sf::Color::Green);
    levelText.setPosition(window.getSize().x / 2 - 50, 10);

    // Load textures
    if (!loadTextures()) {
        logError("Game", "Failed to load some textures");
    }

    std::cout << "[Game] Constructor completed" << std::endl;
}

/**
 * @brief Destructor
 */
Game::~Game() {
    std::cout << "[Game] Destructor called" << std::endl;
    cleanup();
}

// ===== INITIALIZATION =====

/**
 * @brief Initialize a new game
 */
void Game::initialize() {
    std::cout << "[Game] initialize() called" << std::endl;

    // Create grid system
    if (grid == nullptr) {
        grid = new GameGrid(1200, 800);
    }

    // Create collision manager
    if (collisionManager == nullptr) {
        collisionManager = new CollisionManager(grid);
    }

    // Get settings from SettingsScreen
    SettingsScreen* settings = 
        (SettingsScreen*)screenManager.getScreen(GameState::SETTINGS);

    if (settings != nullptr) {
        lives = settings->getLives();
        level = settings->getSpawnLevel();
        int playerIcon = settings->getSelectedPlayerIcon();

        std::cout << "[Game] Loaded settings: Lives=" << lives
                  << ", Level=" << level
                  << ", PlayerIcon=" << playerIcon << std::endl;
    }

    // Reset score
    score = 0;
    isGameOver = false;
    isPaused = false;

    // Create player
    if (player == nullptr) {
        player = new Player(grid, playerTexture);
    } else {
        player->reset();
    }

    // Clear existing objects
    for (auto centipede : centipedes) {
        delete centipede;
    }
    centipedes.clear();

    for (auto bullet : bullets) {
        delete bullet;
    }
    bullets.clear();

    for (auto mushroom : mushrooms) {
        delete mushroom;
    }
    mushrooms.clear();

    // Create initial centipede
    createInitialCentipede();

    // Generate mushrooms
    generateMushrooms();

    std::cout << "[Game] Game initialized - ready to play!" << std::endl;
}

// ===== GAME LOOP =====

/**
 * @brief Handle input
 */
void Game::handleInput(const sf::Event& event) {
    if (isGameOver) {
        return;
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::P) {
            isPaused = !isPaused;
            if (isPaused) {
                currentState = GameState::PAUSED;
                std::cout << "[Game] Paused" << std::endl;
            } else {
                currentState = GameState::PLAYING;
                std::cout << "[Game] Resumed" << std::endl;
            }
        }
    }

    // Only handle game input if not paused
    if (isPaused) {
        return;
    }

    // Continuous input handled in update()
}

/**
 * @brief Update game logic
 */
void Game::update(float dt) {
    if (isPaused || isGameOver) {
        return;
    }

    // Handle keyboard input (continuous)
    handleKeyboardInput();

    // Update player
    if (player) {
        player->update(dt);
    }

    // Update all centipedes
    for (auto centipede : centipedes) {
        if (centipede) {
            centipede->update(dt);
        }
    }

    // Update all bullets
    for (auto bullet : bullets) {
        if (bullet) {
            bullet->update(dt);
        }
    }

    // Update all mushrooms
    for (auto mushroom : mushrooms) {
        if (mushroom) {
            mushroom->update(dt);
        }
    }

    // Update UI
    updateUI();

    // Handle all collisions
    handleCollisions();

    // Clean up dead objects
    cleanupDeadBullets();
    cleanupDestroyedMushrooms();
    cleanupDeadCentipedes();

    // Check win/lose conditions
    checkGameOver();
    if (centipedes.empty() && !isGameOver) {
        completeLevel();
    }

    // Update UI
    updateUI();
}

/**
 * @brief Render all objects
 */
void Game::render() {
    // Draw background
    window.draw(background);

    // Draw mushrooms
    for (auto mushroom : mushrooms) {
        if (mushroom) {
            window.draw(*mushroom);
        }
    }

    // Draw centipedes
    for (auto centipede : centipedes) {
        if (centipede) {
            window.draw(*centipede);
        }
    }

    // Draw bullets
    for (auto bullet : bullets) {
        if (bullet && bullet->isAlive()) {
            window.draw(*bullet);
        }
    }

    // Draw player
    if (player) {
        window.draw(*player);
    }

    // Draw UI text
    window.draw(scoreText);
    window.draw(livesText);
    window.draw(levelText);
}

// ===== STATE MANAGEMENT =====

/**
 * @brief Get current state
 */
GameState Game::getState() const {
    return currentState;
}

/**
 * @brief Set game state
 */
void Game::setState(GameState newState) {
    if (newState != currentState) {
        currentState = newState;
        std::cout << "[Game] State changed to " << static_cast<int>(newState) << std::endl;
    }
}

// ===== CLEANUP =====

/**
 * @brief Clean up all resources
 */
void Game::cleanup() {
    std::cout << "[Game] cleanup() called" << std::endl;

    // Delete player
    if (player != nullptr) {
        delete player;
        player = nullptr;
    }

    // Delete centipedes
    for (auto centipede : centipedes) {
        delete centipede;
    }
    centipedes.clear();

    // Delete bullets
    for (auto bullet : bullets) {
        delete bullet;
    }
    bullets.clear();

    // Delete mushrooms
    for (auto mushroom : mushrooms) {
        delete mushroom;
    }
    mushrooms.clear();

    // Delete systems
    if (collisionManager != nullptr) {
        delete collisionManager;
        collisionManager = nullptr;
    }

    if (grid != nullptr) {
        delete grid;
        grid = nullptr;
    }

    std::cout << "[Game] Cleanup completed" << std::endl;
}

// ===== PRIVATE HELPER FUNCTIONS =====

/**
 * @brief Load all textures
 */
bool Game::loadTextures() {
    bool allLoaded = true;

    // Load single atlas texture that contains all sprites
    if (!playerTexture.loadFromFile("assets/sprites/atlas.png")) {
        logError("Game", "Failed to load atlas texture");
        return false;
    }

    // All textures point to the same atlas, but use different IntRects
    centipedeHeadTexture = playerTexture;
    centipedeBodyTexture = playerTexture;
    centipedeTailTexture = playerTexture;
    mushroomTexture = playerTexture;
    bulletTexture = playerTexture;

    std::cout << "[Game] Atlas texture loaded successfully" << std::endl;
    return true;
}

/**
 * @brief Generate mushroom obstacles
 */
void Game::generateMushrooms() {
    // Generate 15-20 mushrooms based on level
    int mushroomCount = 15 + (level * 2);

    for (int i = 0; i < mushroomCount; i++) {
        auto [gridX, gridY] = grid->getRandomEmptyCell();

        Mushroom* mushroom = new Mushroom(grid, mushroomTexture, gridX, gridY, 4, NORMAL);
        mushrooms.push_back(mushroom);
    }

    std::cout << "[Game] Generated " << mushrooms.size() << " mushrooms" << std::endl;
}

/**
 * @brief Create initial centipede
 */
void Game::createInitialCentipede() {
    int length = 10 + (level * 2);  // Longer centipedes on higher levels

    Centipede* centipede = new Centipede(
        grid,
        centipedeHeadTexture,
        centipedeBodyTexture,
        centipedeTailTexture,
        length,
        MOVING_RIGHT
    );

    centipedes.push_back(centipede);

    std::cout << "[Game] Created centipede with " << length << " segments" << std::endl;
}

/**
 * @brief Handle all collisions
 */
void Game::handleCollisions() {
    processBulletCentipedeCollisions();
    processBulletMushroomCollisions();
    checkPlayerCentipedeCollisions();
}

/**
 * @brief Handle keyboard input
 */
void Game::handleKeyboardInput() {
    if (!player) return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player->moveLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player->moveRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player->moveUp();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player->moveDown();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (player->canShoot()) {
            auto [bulletX, bulletY] = player->shoot();

            if (bulletX >= 0 && bulletY >= 0) {
                Bullet* bullet = new Bullet(grid, bulletTexture, bulletX, bulletY);
                bullets.push_back(bullet);
            }
        }
    }
}

/**
 * @brief Process bullet vs centipede collisions
 */
void Game::processBulletCentipedeCollisions() {
    for (int b = 0; b < static_cast<int>(bullets.size()); b++) {
        if (!bullets[b] || !bullets[b]->isAlive()) {
            continue;
        }

        for (int c = 0; c < static_cast<int>(centipedes.size()); c++) {
            if (!centipedes[c]) {
                continue;
            }

            CollisionResult result = collisionManager->checkBulletCentipede(bullets[b], centipedes[c]);

            if (result.collided) {
                bullets[b]->kill();
                score += 100;

                Centipede* newCentipede = centipedes[c]->shootSegment(result.data);

                if (newCentipede != nullptr) {
                    centipedes.push_back(newCentipede);
                }

                break;
            }
        }
    }
}

/**
 * @brief Process bullet vs mushroom collisions
 */
void Game::processBulletMushroomCollisions() {
    for (int b = 0; b < static_cast<int>(bullets.size()); b++) {
        if (!bullets[b] || !bullets[b]->isAlive()) {
            continue;
        }

        Mushroom* hitMushroom = collisionManager->checkBulletMushroom(bullets[b], mushrooms);

        if (hitMushroom) {
            bullets[b]->kill();

            if (hitMushroom->takeDamage()) {
                score += 10;  // Mushroom destroyed
            } else {
                score += 5;   // Mushroom damaged
            }
        }
    }
}

/**
 * @brief Check player vs centipede collisions
 */
void Game::checkPlayerCentipedeCollisions() {
    if (!player) return;

    if (collisionManager->checkPlayerCentipedes(player, centipedes)) {
        playerDeath();
    }
}

/**
 * @brief Complete level
 */
void Game::completeLevel() {
    level++;
    score += 1000;  // Bonus for level completion

    std::cout << "[Game] Level complete! Moving to level " << level << std::endl;

    // Clear mushrooms
    for (auto mushroom : mushrooms) {
        delete mushroom;
    }
    mushrooms.clear();

    // Create new centipede and mushrooms
    createInitialCentipede();
    generateMushrooms();
}

/**
 * @brief Handle player death
 */
void Game::playerDeath() {
    lives--;
    std::cout << "[Game] Player died! Lives remaining: " << lives << std::endl;

    if (lives > 0) {
        player->reset();
    }
}

/**
 * @brief Check game over
 */
void Game::checkGameOver() {
    if (lives <= 0) {
        isGameOver = true;
        currentState = GameState::GAME_OVER;
        std::cout << "[Game] GAME OVER! Final score: " << score << std::endl;
    }
}

/**
 * @brief Clean up dead bullets
 */
void Game::cleanupDeadBullets() {
    for (int i = 0; i < static_cast<int>(bullets.size()); i++) {
        if (!bullets[i]->isAlive()) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }
}

/**
 * @brief Clean up destroyed mushrooms
 */
void Game::cleanupDestroyedMushrooms() {
    for (int i = 0; i < static_cast<int>(mushrooms.size()); i++) {
        if (mushrooms[i]->isDestroyed()) {
            delete mushrooms[i];
            mushrooms.erase(mushrooms.begin() + i);
            i--;
        }
    }
}

/**
 * @brief Clean up dead centipedes
 */
void Game::cleanupDeadCentipedes() {
    for (int i = 0; i < static_cast<int>(centipedes.size()); i++) {
        if (!centipedes[i]->isAlive()) {
            delete centipedes[i];
            centipedes.erase(centipedes.begin() + i);
            i--;
        }
    }
}

/**
 * @brief Update UI text
 */
void Game::updateUI() {
    scoreText.setString("Score: " + std::to_string(score));
    livesText.setString("Lives: " + std::to_string(lives));
    levelText.setString("Level: " + std::to_string(level));
}

/**
 * @brief Debug print
 */
void Game::debugPrint() const {
    std::cout << "\n[Game] Debug Info:" << std::endl;
    std::cout << "  Score: " << score << std::endl;
    std::cout << "  Lives: " << lives << std::endl;
    std::cout << "  Level: " << level << std::endl;
    std::cout << "  Centipedes: " << centipedes.size() << std::endl;
    std::cout << "  Bullets: " << bullets.size() << std::endl;
    std::cout << "  Mushrooms: " << mushrooms.size() << std::endl;
    std::cout << std::endl;
}