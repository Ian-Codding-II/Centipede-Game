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
#include "mushroom.h"

//class Player;



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
  public:
    Player player;
    Bullet bullet;
    sf::RectangleShape playerShape;
    sf::Texture playerTexture;
    sf::RectangleShape bulletShape;
    sf::Texture bulletTexture;
    sf::RenderWindow& window;
    int bulletCount = 0;
    std::vector<Mushroom> mushrooms;


    Game();
    Game(sf::RenderWindow& win, ScreenManager& sm);
    ~Game() {};

    void handleInput(sf::RectangleShape& playrect, Player* obj, Bullet* obj2, float dt);
    void update(float time);
    void render();
    bool isDone() const;
    void initializeGame();
    void cleanup();

    bool checkCollision(); 

    void addScore(); 

    bool loseLife() ;

    void completLevel();

    bool damageCentipedeSegment(int segmentIndex);

    void resetAfterDeath(); 

    GameState getState() const;




  private:
    

    // Private members
};
// - Initialize SFML window
// - Manage game states (Menu, Playing, Paused, GameOver)
// - Handle state transitions
// - Coordinate update loop
// - Render all objects