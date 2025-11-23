/**
 * @file game.h
 * @author Ian Codding II
 * @brief Decleration of Game class - main gameplay logic
 * @version 0.1
 * @date 2025-10-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "bullet.h"
#include "Centipede_Segment.h"
#include "Collision_Manager.h"
#include "Game_State.h"
#include "player.h"
#include "ScreenManager.h"
#include "SettingsScreen.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>

// Forward declarations - these classes exist but we onl need pointers to them
// This avoids circular includes
class Player;
class Centipede;
class Bullet;
class Mushroom;

/**
 * @class Game
 * @brief Main game class that handels all gameplay logic
 *
 */
class Game {

  private:
    sf::RenderWindow &window;
    ScreenManager &screenManager;

    GameState currentState;
    bool isGameOver;
    bool isPaused;

    int score;
    int lives;
    int level;

    Player *player;
    Centipede *centipede;
    // If we ever make the spider class,
    // then we would have a pointer to spider

    std::vector<Bullet *> bullets;
    std::vector<Mushroom *> mushrooms;

    sf::Text scoreText; // Displays current score
    sf::Text livesText; // Displays remaining lives
    sf::Text levelText; // Displays current level

    sf::RectangleShape background; // Black background rectangle

  public:
    Game(sf::RenderWindow &win, ScreenManager &screenMngr);

    ~Game();

    void initualize();

    void handleInput(const sf::Event &event);

    void update(float dt);

    void render();

    GameState getState() const;

    void cleanup();

    bool checkCollision();

    void addScore();

    bool loseLife();

    void completLevel();

    bool damageCentipedeSegment(int segmentIndex);

    void resetAfterDeath();
};
// - Initialize SFML window
// - Manage game states (Menu, Playing, Paused, GameOver)
// - Handle state transitions
// - Coordinate update loop
// - Render all objects