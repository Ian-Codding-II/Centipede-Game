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
class Game {
public:
    Game();
    ~Game() {};
    void handleInput();
    void update(float time);
    void render();
    bool isDone() const;

    private:
    sf::RenderWindow mWindow;
    bool mIsDone;
    sf::Texture mTextureTile;
    sf::Vector2f mIncrement;
};
// - Initialize SFML window
// - Manage game states (Menu, Playing, Paused, GameOver)
// - Handle state transitions
// - Coordinate update loop
// - Render all objects