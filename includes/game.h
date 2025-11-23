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

class Game {
  public:
    Game();
    Game(sf::RenderWindow& win, ScreenManager& sm);
    ~Game() {};
    void handleInput(sf::RectangleShape& playrect, Player obj);
    void update(float time);
    void render();
    bool isDone() const;
    void initializeGame();
  private:
    
};
// - Initialize SFML window
// - Manage game states (Menu, Playing, Paused, GameOver)
// - Handle state transitions
// - Coordinate update loop
// - Render all objects