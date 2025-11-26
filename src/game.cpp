/**
 * @file game.cpp
 * @author Ian Codding II
 * @brief Implementation of Game class - main gameplay logic
 * @version 0.1
 * @date 2025-10-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../includes/game.h"
#include "../includes/errorHandler.h"
#include "../includes/ScreenManager.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

/**
 * @brief Construct a new Game:: Game object
 *
 */
Game::Game(sf::RenderWindow &win, ScreenManager &screenMngr)
    : window(win)
    , screenManager(screenMngr)
    , currentState(GameState::PLAYING)
    , isGameOver(false)
    , isPaused(false)
    , score(0)
    , lives(3)
    , level(1)
    , player(nullptr)
    , centipede(nullptr) {

    std::cout << "[Game] Constructor called\n";

    // ===== SET UP TEXT DISPLAYS =====
    // IMPORTANT: Get the font from ScreenManager (shared font loaded there)
    sf::Font &font = screenManager.getFont();

    // Set up the black background
    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color::Black);

    // Set up score text
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::Green);
    scoreText.setPosition(10, 10);

    // Set up lives text
    livesText.setFont(font);
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::Green);
    livesText.setPosition(window.getSize().x - 200, 10);

    // Set up level text
    levelText.setFont(font);
    levelText.setCharacterSize(20);
    levelText.setFillColor(sf::Color::Green);
    levelText.setPosition(window.getSize().x / 2 - 50, 10);

    std::cout << "[Game] Game object fully initialized\n";
}

Game::~Game() {
}

/**
 * @brief Initialize a new game
 *
 * Sets up a fresh game state:
 * - Resets score and lives
 * - Creates player at bottom center
 * - Creates centipede at top
 * - Populates mushroom obstacles
 * - Loads settings from SettingsScreen
 *
 * This is called:
 * 1. When game first starts
 * 2. When player clicks "Play Again" after Game Over
 * 3. When transitioning from MENU to PLAYING state
 *
 */
void Game::initialize() {
    std::cout << "[Game] initialize() called - starting new game" << std::endl;

    // ===== GET SETTINGS FROM SETTINGS SCREEN =====
    SettingsScreen* settings = 
        (SettingsScreen*)screenManager.getScreen(GameState::SETTINGS);

    if (settings != nullptr) {
        lives = settings->getLives();
        level = settings->getSpawnLevel();
        int playerIcon = settings->getSelectedPlayerIcon();
        
        std::cout << "[Game] Loaded settings: Lives=" << lives
                  << ", Level=" << level
                  << ", PlayerIcon=" << playerIcon << std::endl;
    } else {
        logError("Game", "Could not get SettingsScreen - using defaults");
        lives = 3;
        level = 1;
    }

    // ===== RESET SCORE (but keep from previous attempts? Your choice) =====
    score = 0;
    isGameOver = false;
    isPaused = false;

    // ===== CREATE PLAYER =====
    // Player starts at bottom center of screen
    if (player == nullptr) {
        player = new Player();
        // You'll need to implement Player initialization based on your Player class
        // Example: player->setPosition(window.getSize().x / 2, window.getSize().y - 50);
        std::cout << "[Game] Player created" << std::endl;
    } else {
        // If player already exists, just reset position
        // player->reset();
    }

    // ===== CREATE CENTIPEDE =====
    // Centipede starts at top center with length based on level
    if (centipede == nullptr) {
        // centipede = new Centipede();
        // Initialize centipede with head at (window center, top)
        // Length = 10 + (level * 2)
        // std::cout << "[Game] Centipede created with length: " << (10 + level * 2) << std::endl;
    } else {
        // If centipede already exists, reset it
        // centipede->reset();
    }

    // ===== CREATE MUSHROOM OBSTACLES =====
    // Clear any existing mushrooms
    for (auto mushroom : mushrooms) {
        if (mushroom != nullptr) {
            delete mushroom;
        }
    }
    mushrooms.clear();

    // Create random mushrooms scattered around the screen
    // Roughly 15-20 mushrooms per level
    int mushroomCount = 15 + (level * 2);
    for (int i = 0; i < mushroomCount; i++) {
        // Random position (not at top or bottom where player/centipede start)
        float randX = 50 + rand() % (static_cast<int>(window.getSize().x) - 100);
        float randY = 100 + rand() % (static_cast<int>(window.getSize().y) - 200);

        // Mushroom* mushroom = new Mushroom();
        // mushroom->setPosition(randX, randY);
        // mushrooms.push_back(mushroom);
    }
    std::cout << "[Game] Created " << mushrooms.size() << " mushrooms" << std::endl;

    std::cout << "[Game] Game initialization complete - ready to play!" << std::endl;
}

/**
 * @brief Handle keyboard and mouse input
 *
 * Processes player input:
 * - WASD / Arrow keys: Move player
 * - SPACE: Shoot bullet
 * - ESC: Pause game
 *
 * @param event The SFML event containing input information
 */
void Game::handleInput(const sf::Event& event) {
    // Only process input if we're playing (not paused)
    if (isPaused) {
        return;
    }

    // Keyboard input
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Escape:
            // Pause the game
            isPaused = true;
            currentState = GameState::PAUSED;
            std::cout << "[Game] ESC pressed - pausing game" << std::endl;
            break;

        case sf::Keyboard::Space:
            // Player shoots
            if (player != nullptr) {
                // player->shoot();
                std::cout << "[Game] Player shot a bullet" << std::endl;
            }
            break;

        case sf::Keyboard::Left:
        case sf::Keyboard::A:
            // Move player left (handled in update with continuous input)
            break;

        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            // Move player right (handled in update with continuous input)
            break;

        default:
            break;
        }
    }
}

void Game::update(float dt) {
}

void Game::render() {
    // ===== DRAW BACKGROUND =====
    // Black rectangle covering entire screen
    window.draw(background);
    // This will be at the top.

    // There will be more to draw, but this will be at the bottom
    // ===== DRAW UI TEXT =====
    // Update and draw score text
    scoreText.setString("Score: " + std::to_string(score));
    window.draw(scoreText);

    // Update and draw lives text
    livesText.setString("Lives: " + std::to_string(lives));
    window.draw(livesText);

    // Update and draw level text
    levelText.setString("Level: " + std::to_string(level));
    window.draw(levelText);
}

/**
 * @brief Get the current game state
 *
 * Returns the current GameState enum value.
 * Used by main.cpp to determine whether to render game or UI.
 *
 * @return Current GameState (PLAYING, PAUSED, GAME_OVER, etc.)
 */
GameState Game::getState() const {
    return currentState;
}

void Game::cleanup() {
}

bool Game::checkCollision() {
}

/**
 * @brief Add points to the score
 *
 * Increases score and updates the score text.
 * Called when:
 * - Bullet hits centipede segment
 * - Bullet hits mushroom
 * - Enemy is defeated
 *
 * Could also check for leaderboard qualifications here.
 *
 * @param points Points to add to score
 */
void Game::addScore() {
    // This should probably take an int parameter for points
    // For now, we'll add 10 points
    score += 10;
    std::cout << "[Game] Score increased to " << score << std::endl;
}

/**
 * @brief Remove one life from the player
 *
 * Called when player collides with centipede.
 * Decreases lives counter and checks for game over.
 *
 * @return true if game is over (no lives left), false otherwise
 */
bool Game::loseLife() {
    lives--;
    std::cout << "[Game] Lost a life! Lives remaining: " << lives << std::endl;

    if (lives <= 0) {
        isGameOver = true;
        return true;
    }
    return false;
}

/**
 * @brief Complete current level
 *
 * Called when centipede is completely destroyed.
 * Increases level and spawns new centipede.
 *
 * Could also:
 * - Award bonus points for completing level
 * - Speed up centipede for next level
 * - Add more mushrooms for next level
 * - Show level complete message
 */
void Game::completLevel() {
    level++;
    std::cout << "[Game] Level " << (level - 1) << " complete! Moving to level " << level << std::endl;

    // Reset centipede for new level
    if (centipede != nullptr) {
        delete centipede;
        // centipede = new Centipede();
        // centipede->setLevel(level);  // Increase speed/length for new level
    }

    // Award bonus points
    addScore();
}

bool Game::damageCentipedeSegment(int segmentIndex) {
}

/**
 * @brief Reset after player death
 *
 * Called after player loses a life.
 * Resets:
 * - Player position to starting position
 * - Removes player's bullets
 * - Centipede continues moving
 *
 * If lives > 0: Game continues
 * If lives <= 0: Game over
 */
void Game::resetAfterDeath() {
    std::cout << "[Game] Resetting after death..." << std::endl;

    // Clear player's bullets
    for (auto bullet : bullets) {
        if (bullet != nullptr) {
            delete bullet;
        }
    }
    bullets.clear();

    // Reset player to starting position
    if (player != nullptr) {
        // player->reset();  // Reset position to bottom center
        // player->resetShootCooldown();
    }

    std::cout << "[Game] Reset complete" << std::endl;
}