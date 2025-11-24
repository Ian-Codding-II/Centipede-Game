/**
 * @file game.h
 * @author Ian Codding II
 * @brief 
 * @version 0.1
 * @date 2025-10-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <SFML/Graphics.hpp>
#include "ScreenManager.h"
#include "player.h"

//class Player;



class Game {
  public:
    Player player;
    Bullet bullet;
    sf::RectangleShape playerShape;
    sf::Texture playerTexture;
    sf::RectangleShape bulletShape;
    sf::Texture bulletTexture;
    sf::RenderWindow& window;
    
    Game();
    Game(sf::RenderWindow& win, ScreenManager& sm);
    ~Game() {};

    void handleInput(sf::RectangleShape& playerShape, Player* player);
    void update(float time);
    void render();
    bool isDone() const;
    void initializeGame();
  private:
    

    // Private members
};
// - Initialize SFML window
// - Manage game states (Menu, Playing, Paused, GameOver)
// - Handle state transitions
// - Coordinate update loop
// - Render all objects