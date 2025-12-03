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
 * Orchestrates gameplay: player, bullets, mushrooms, centipede
 * Objects handle their own collision and grid management
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
    void debugPrint() const;
    
    /**
     * @brief Save player name and score to leaderboard
     * @param playerName Name entered by player
     */
    void savePlayerScore(const std::string& playerName);

private:
    sf::RenderWindow& window;
    ScreenManager& screenManager;

    GameState currentState;
    bool isGameOver;
    bool isPaused;

    sf::RectangleShape* player;
    Centipede* centipede;
    Bullet bulletObj;
    std::vector<Mushroom*> mushrooms;
    Grid* grid;

    int score;
    int lives;
    int level;

    sf::RectangleShape background;
    sf::Text scoreText;
    sf::Text livesText;
    sf::Text levelText;

    sf::Texture texture;

    bool loadTextures();
    void generateMushrooms();
    void checkGameOver();
    void updateUI();
};

#endif // GAME_H