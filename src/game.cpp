/**
 * @file game.cpp
 * @author Ian Codding II
 * @brief Implementation of Game class - WITHOUT centipede for now
 * @version 2.1 - Testing player, bullets, and mushrooms only
 * @date 2025-11-26
 *
 * @copyright Copyright (c) 2025
 */

#include "../includes/game.h"
#include "../includes/errorHandler.h"
#include "../includes/GameGrid.h"
#include <iostream>
#include <cstdlib>

/**
 * @brief Constructor - initialize the game
 */
Game::Game(sf::RenderWindow& win, ScreenManager& screenMngr)
    : window(win),
      screenManager(screenMngr),
      currentState(GameState::PLAYING),
      isGameOver(false),
      isPaused(false),
      score(0),
      lives(3),
      level(1),
      player(nullptr),
      centipede(nullptr),
      grid(nullptr),
      playerTexture(),
      mushroomTexture(),
      bulletTexture() {

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

    // Create game grid
    if (grid == nullptr) {
        grid = new GameGrid(1200, 800);
        std::cout << "[Game] Game grid created (1200x800, 32x32 cells)" << std::endl;
    } else {
        // Clear grid if reinitializing
        delete grid;
        grid = new GameGrid(1200, 800);
    }

    // Get settings from SettingsScreen
    SettingsScreen* settings = 
        (SettingsScreen*)screenManager.getScreen(GameState::SETTINGS);

    if (settings != nullptr) {
        lives = settings->getLives();
        level = settings->getSpawnLevel();

        std::cout << "[Game] Loaded settings: Lives=" << lives
                  << ", Level=" << level << std::endl;
    }

    // Reset score
    score = 0;
    isGameOver = false;
    isPaused = false;

    // Create player using Roman's startPlayer function
    player = new sf::RectangleShape();
    Player::startPlayer(*player, playerTexture);

    // Generate initial mushrooms
    generateMushrooms();

    std::cout << "[Game] Game initialized - ready to play!" << std::endl;
    std::cout << "[Game] Testing: Player, Bullets, and Mushrooms only (no centipede yet)" << std::endl;
}

// ===== GAME LOOP =====

/**
 * @brief Handle input events
 */
void Game::handleInput(const sf::Event& event) {
    if (isGameOver) {
        return;
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::P) {
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
}

/**
 * @brief Update game logic
 */
void Game::update(float dt) {
    if (isPaused || isGameOver) {
        return;
    }

    // Update player movement using Roman's code
    if (player) {
        Player::movePlayer(*player, dt);
    }

    // Update bullets - handle shooting and movement
    // Create a temporary bullet shape for new bullets
    sf::RectangleShape tempBullet;
    tempBullet.setSize(sf::Vector2f(10.f, 10.f));
    bulletObj.isShooting(*player, tempBullet, bulletTexture, bulletObj, dt);
    
    // Move bullets upward
    for (int i = static_cast<int>(bulletObj.bullets.size()) - 1; i >= 0; i--) {
        sf::Vector2f bulletPos = bulletObj.bullets[i].getPosition();
        bulletPos.y -= 500 * dt;  // Move up at 500 pixels/second
        bulletObj.bullets[i].setPosition(bulletPos);
        
        // Remove if off-screen
        if (bulletPos.y < 0) {
            bulletObj.bullets.erase(bulletObj.bullets.begin() + i);
            std::cout << "[Game] Bullet removed (off-screen)" << std::endl;
        }
    }

    // Update mushrooms
    for (auto mushroom : mushrooms) {
        if (mushroom) {
            mushroom->update();
        }
    }

    // Check collisions (bullets vs mushrooms ONLY for now)
    handleCollisions();

    // Clean up destroyed mushrooms
    for (int i = mushrooms.size() - 1; i >= 0; i--) {
        // Check if mushroom is destroyed by trying to get its state
        // Since there's no public health getter, we check if it doesn't render anymore
        // For now, we'll keep all mushrooms - destruction is handled by hit()
    }

    // Update UI
    updateUI();

    // Check game over condition
    checkGameOver();

    // Debug output
    static int frameCount = 0;
    if (++frameCount % 60 == 0) {  // Every 60 frames
        debugPrint();
    }
}

/**
 * @brief Render all game objects
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

    // Draw bullets
    for (auto& bullet : bulletObj.bullets) {
        window.draw(bullet);
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
 * @brief Get current game state
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

    // Clear mushrooms
    for (auto mushroom : mushrooms) {
        if (mushroom != nullptr) {
            delete mushroom;
        }
    }
    mushrooms.clear();

    // Clear bullets
    bulletObj.bullets.clear();

    // Delete grid
    if (grid != nullptr) {
        delete grid;
        grid = nullptr;
    }

    std::cout << "[Game] Cleanup completed" << std::endl;
}

// ===== PRIVATE HELPER FUNCTIONS =====

/**
 * @brief Load all textures from atlas
 */
bool Game::loadTextures() {
    // Load single atlas texture
    if (!playerTexture.loadFromFile("assets/sprites/atlas.png")) {
        logError("Game", "Failed to load player texture");
        return false;
    }

    // All textures point to same atlas
    mushroomTexture = playerTexture;
    bulletTexture = playerTexture;

    std::cout << "[Game] All textures loaded successfully" << std::endl;
    return true;
}

/**
 * @brief Generate mushroom obstacles using grid
 */
void Game::generateMushrooms() {
    if (grid == nullptr) {
        std::cerr << "[Game] ERROR: Grid not initialized for mushroom generation!" << std::endl;
        return;
    }

    int mushroomCount = 10 + (level * 2);

    std::cout << "[Game] Generating " << mushroomCount << " mushrooms..." << std::endl;

    for (int i = 0; i < mushroomCount; i++) {
        // Get random empty cell from grid
        auto [gridX, gridY] = grid->getRandomEmptyCell();

        // Convert grid coordinates to pixel coordinates (center of cell)
        sf::Vector2f pixelPos = grid->gridToCenterPixel(gridX, gridY);

        // Create mushroom using Balin's class
        // Mushroom(texture, spriteTexture, position, health, isSuper)
        Mushroom* mushroom = new Mushroom(
            mushroomTexture,
            sf::IntRect(64, 64, 32, 32),  // Mushroom sprite in atlas - ADJUST IF NEEDED
            sf::Vector2i(static_cast<int>(pixelPos.x), static_cast<int>(pixelPos.y)),
            4,      // Health (4 hits to destroy)
            false   // Not super
        );
        
        // Mark mushroom location on grid
        grid->setOccupied(gridX, gridY, MUSHROOM);
        
        mushrooms.push_back(mushroom);
    }

    std::cout << "[Game] Created " << mushrooms.size() << " mushrooms" << std::endl;
}

/**
 * @brief Handle all collisions
 * 
 * Currently tests: Bullets vs Mushrooms only
 * Uses public API for Balin's Mushroom class
 */
void Game::handleCollisions() {
    if (!player || !grid) return;

    // ===== CHECK BULLET vs MUSHROOM COLLISIONS =====
    for (int b = static_cast<int>(bulletObj.bullets.size()) - 1; b >= 0; b--) {
        sf::FloatRect bulletBounds = bulletObj.bullets[b].getGlobalBounds();

        for (int m = 0; m < static_cast<int>(mushrooms.size()); m++) {
            // Get mushroom position using public getPosition()
            sf::Vector2i mushroomPos = mushrooms[m]->getPosition();
            
            // Estimate mushroom bounds (32x32 sprite, origin at center)
            sf::FloatRect mushroomBounds(mushroomPos.x - 16, mushroomPos.y - 16, 32, 32);

            if (bulletBounds.intersects(mushroomBounds)) {
                // Hit mushroom!
                std::cout << "[Game] Bullet hit mushroom!" << std::endl;
                
                bulletObj.bullets.erase(bulletObj.bullets.begin() + b);
                mushrooms[m]->hit(1);  // Damage mushroom by 1 HP
                score += 5;

                // Clear mushroom from grid
                int mushX = grid->pixelToGridX(mushroomPos.x);
                int mushY = grid->pixelToGridY(mushroomPos.y);
                grid->clearOccupied(mushX, mushY, MUSHROOM);

                std::cout << "[Game] Score: " << score << std::endl;
                return;  // Exit to avoid checking more after erasing
            }
        }
    }
}

/**
 * @brief Check if game is over
 */
void Game::checkGameOver() {
    // For now, game ends if lives <= 0
    // TODO: Add centipede collision check later
    
    if (lives <= 0) {
        isGameOver = true;
        currentState = GameState::GAME_OVER;
        std::cout << "[Game] GAME OVER! Final score: " << score << std::endl;
    }
}

/**
 * @brief Update UI text displays
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
    std::cout << "\n[Game] === DEBUG INFO ===" << std::endl;
    std::cout << "  Score: " << score << std::endl;
    std::cout << "  Lives: " << lives << std::endl;
    std::cout << "  Level: " << level << std::endl;
    std::cout << "  Bullets: " << bulletObj.bullets.size() << std::endl;
    std::cout << "  Mushrooms: " << mushrooms.size() << std::endl;
    
    if (player) {
        std::cout << "  Player pos: (" << player->getPosition().x << ", " 
                  << player->getPosition().y << ")" << std::endl;
    }
    std::cout << std::endl;
}