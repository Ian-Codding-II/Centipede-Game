/**
 * @file game.h
 * @author Ian Codding II
 * @brief Header for Game class - main game controller
 * @version 3.2 - Complete integration
 * @date 2025-12-03
 * @copyright Copyright (c) 2025
 */

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Game_State.h"
#include "ScreenManager.h"
#include "grid.h"
#include "player.h"
#include "bullet.h"
#include "Centipede.h"
#include "mushroom.h"
#include "SettingsScreen.h"
#include "GameOverScreen.h"
#include "LeaderboardScreen.h"

/**
 * @brief Main Game class
 * Orchestrates gameplay: updates player, bullets, mushrooms,
 * centipede. Handles all collision detection. Manages game state.
 */
class Game {
public:
    Game(sf::RenderWindow& win, ScreenManager& screenMngr);
    ~Game();

    void initialize();
    void handleInput(const sf::Event& event);
    void update(float dt);
    void render();

    GameState getState() const;
    void setState(GameState newState);

    void cleanup();
    void setPaused(bool paused);
    bool getPaused() const;
    void savePlayerScore(const std::string& playerName);
    void debugPrint() const;

private:
    sf::RenderWindow& window;
    ScreenManager& screenManager;

    GameState currentState;
    bool isGameOver;
    bool isPaused;

    int score;
    int lives;
    int level;

    sf::RectangleShape* player;
    Centipede* centipede;
    std::vector<Mushroom*> mushrooms;
    Grid* grid;

    sf::RectangleShape background;
    sf::Text scoreText;
    sf::Text livesText;
    sf::Text levelText;

    sf::Texture texture;

    bool loadTextures();
    void generateMushrooms();
    void handleCollisions();
    void checkGameOver();
    void updateUI();
};

#endif // GAME_H