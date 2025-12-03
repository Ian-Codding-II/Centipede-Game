/**
 * @file game.h
 * @author Ian Codding II
 * @brief Header for Game class - integrated with existing classes
 * @version 2.0 - Compatible with Balin's and Roman's code
 * @date 2025-11-26
 *
 * @copyright Copyright (c) 2025
 */

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Game_State.h"
#include "ScreenManager.h"
#include "GameGrid.h"
#include "player.h"
#include "bullet.h"
#include "Centipede.h"
#include "mushroom.h"
#include "SettingsScreen.h"

/**
 * @brief Main Game class
 *
 * Manages the main game loop, all game objects, and game state.
 * Integrates with:
 * - Roman's Player class
 * - Balin's Centipede class
 * - Balin's Mushroom class
 * - Your Bullet and collision system
 */
class Game {
public:
    /**
     * @brief Constructor
     *
     * @param win Reference to the main window
     * @param screenMngr Reference to the ScreenManager
     */
    Game(sf::RenderWindow& win, ScreenManager& screenMngr);

    /**
     * @brief Destructor
     */
    ~Game();

    // ===== GAME LOOP =====

    /**
     * @brief Initialize the game
     *
     * Called once at the start of gameplay.
     * Sets up all game objects and initial state.
     */
    void initialize();

    /**
     * @brief Handle input events
     *
     * @param event The SFML event to process
     */
    void handleInput(const sf::Event& event);

    /**
     * @brief Update game logic
     *
     * @param dt Delta time since last frame (seconds)
     */
    void update(float dt);

    /**
     * @brief Render all game objects
     *
     * Draws everything to the window.
     */
    void render();

    // ===== STATE MANAGEMENT =====

    /**
     * @brief Get current game state
     *
     * @return Current GameState
     */
    GameState getState() const;

    /**
     * @brief Set game state
     *
     * @param newState The new state to transition to
     */
    void setState(GameState newState);

    // ===== CLEANUP =====

    /**
     * @brief Clean up all resources
     *
     * Called before destruction to free memory.
     */
    void cleanup();

    // ===== DEBUG =====

    /**
     * @brief Print debug information
     */
    void debugPrint() const;

private:
    // ===== WINDOW & MANAGER =====
    sf::RenderWindow& window;           ///< Reference to main window
    ScreenManager& screenManager;       ///< Reference to ScreenManager

    // ===== GAME STATE =====
    GameState currentState;             ///< Current game state (PLAYING, PAUSED, etc.)
    bool isGameOver;                    ///< Is game over?
    bool isPaused;                      ///< Is game paused?

    // ===== GAME OBJECTS =====
    sf::RectangleShape* player;         ///< Pointer to player (Roman's class)
    Centipede* centipede;               ///< Pointer to centipede
    Bullet bulletObj;                   ///< Bullet object (handles all bullets)
    std::vector<Mushroom*> mushrooms;   ///< All mushroom obstacles (Balin's class)
    GameGrid* grid;                     ///< Grid system for mushroom positions
    //std::vector<Bullet> bullets;
    std::vector<Bullet*> bullets;


    // ===== GAME STATS =====
    int score;                          ///< Current score
    int lives;                          ///< Remaining lives
    int level;                          ///< Current level

    // ===== RENDERING =====
    sf::RectangleShape background;      ///< Black background
    sf::Text scoreText;                 ///< Score display
    sf::Text livesText;                 ///< Lives display
    sf::Text levelText;                 ///< Level display

    // ===== TEXTURES =====
    sf::Texture playerTexture;          ///< Atlas texture
    sf::Texture centipedeTexture;       ///< Points to atlas
    sf::Texture mushroomTexture;        ///< Points to atlas
    sf::Texture bulletTexture;          ///< Points to atlas

    // ===== PRIVATE HELPER FUNCTIONS =====

    /**
     * @brief Load all game textures
     *
     * @return true if all loaded successfully
     */
    bool loadTextures();

    /**
     * @brief Generate mushroom obstacles
     */
    void generateMushrooms();

    /**
     * @brief Handle all collisions
     */
    void handleCollisions();

    /**
     * @brief Check if game is over (lose condition)
     */
    void checkGameOver();

    /**
     * @brief Update UI text displays
     */
    void updateUI();
};

#endif // GAME_H