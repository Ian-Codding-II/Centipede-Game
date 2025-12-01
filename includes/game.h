/**
 * @file game.h
 * @author Ian Codding II
 * @brief Main Game class - coordinates all gameplay
 * @version 2.0 - Complete Integration
 * @date 2025-11-26
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Game_State.h"
#include "ScreenManager.h"
#include "SettingsScreen.h"
#include "GameGrid.h"
#include "player.h"
#include "Centipede.h"
#include "bullet.h"
#include "mushroom.h"
#include "Collision_Manager.h"

/**
 * @class Game
 * @brief Main game class - manages all gameplay logic
 *
 * Responsibilities:
 * - Manage game state (playing, paused, game over)
 * - Update all game objects each frame
 * - Detect and handle collisions
 * - Render all game objects
 * - Handle score, lives, and level progression
 * - Coordinate with ScreenManager for UI
 */
class Game {
public:
    /**
     * @brief Constructor - create the game
     *
     * @param win Reference to main window
     * @param screenMngr Reference to ScreenManager
     */
    Game(sf::RenderWindow& win, ScreenManager& screenMngr);

    /**
     * @brief Destructor - clean up all resources
     */
    ~Game();

    // ===== INITIALIZATION =====

    /**
     * @brief Initialize a new game
     *
     * Called when player starts a new game.
     * Sets up:
     * - Grid system
     * - Player at starting position
     * - Initial centipede(s)
     * - Mushroom obstacles
     * - Loads settings from SettingsScreen
     */
    void initialize();

    // ===== GAME LOOP =====

    /**
     * @brief Handle input events
     *
     * @param event SFML event from main loop
     */
    void handleInput(const sf::Event& event);

    /**
     * @brief Update all game logic
     *
     * @param dt Delta time since last frame (seconds)
     */
    void update(float dt);

    /**
     * @brief Render all game objects to screen
     */
    void render();

    // ===== STATE MANAGEMENT =====

    /**
     * @brief Get current game state
     *
     * @return Current GameState (PLAYING, PAUSED, GAME_OVER, etc.)
     */
    GameState getState() const;

    /**
     * @brief Set game state (triggers transitions)
     *
     * @param newState State to transition to
     */
    void setState(GameState newState);

    // ===== CLEANUP =====

    /**
     * @brief Clean up all game resources
     *
     * Called when game ends or transitioning to menu.
     */
    void cleanup();

private:
    // ===== REFERENCES =====
    sf::RenderWindow& window;
    ScreenManager& screenManager;

    // ===== GAME STATE =====
    GameState currentState;
    bool isGameOver;
    bool isPaused;

    // ===== GAME SYSTEMS =====
    GameGrid* grid;
    CollisionManager* collisionManager;

    // ===== GAME OBJECTS =====
    Player* player;
    std::vector<Centipede*> centipedes;
    std::vector<Bullet*> bullets;
    std::vector<Mushroom*> mushrooms;

    // ===== GAME STATS =====
    int score;
    int lives;
    int level;

    // ===== RENDERING =====
    sf::Text scoreText;
    sf::Text livesText;
    sf::Text levelText;
    sf::RectangleShape background;

    // ===== TEXTURES =====
    sf::Texture playerTexture;
    sf::Texture centipedeHeadTexture;
    sf::Texture centipedeBodyTexture;
    sf::Texture centipedeTailTexture;
    sf::Texture mushroomTexture;
    sf::Texture bulletTexture;

    // ===== HELPER FUNCTIONS =====

    /**
     * @brief Load all game textures
     *
     * @return true if all textures loaded successfully
     */
    bool loadTextures();

    /**
     * @brief Generate mushroom obstacles
     *
     * Called during initialize() and when completing levels.
     */
    void generateMushrooms();

    /**
     * @brief Create initial centipede
     */
    void createInitialCentipede();

    /**
     * @brief Handle all collisions for this frame
     */
    void handleCollisions();

    /**
     * @brief Handle player input from keyboard
     */
    void handleKeyboardInput();

    /**
     * @brief Process bullet collisions with centipedes
     */
    void processBulletCentipedeCollisions();

    /**
     * @brief Process bullet collisions with mushrooms
     */
    void processBulletMushroomCollisions();

    /**
     * @brief Check if player collides with any centipede
     */
    void checkPlayerCentipedeCollisions();

    /**
     * @brief Handle level progression when centipede is destroyed
     */
    void completeLevel();

    /**
     * @brief Handle player death
     */
    void playerDeath();

    /**
     * @brief Check game over condition
     */
    void checkGameOver();

    /**
     * @brief Clean up dead bullets
     */
    void cleanupDeadBullets();

    /**
     * @brief Clean up destroyed mushrooms
     */
    void cleanupDestroyedMushrooms();

    /**
     * @brief Clean up dead centipedes
     */
    void cleanupDeadCentipedes();

    /**
     * @brief Update UI text displays
     */
    void updateUI();

    /**
     * @brief Debug - print game state to console
     */
    void debugPrint() const;
};