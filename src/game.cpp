/**
 * @file game.cpp
 * @author Ian Codding II
 * @brief 
 * @version 0.1
 * @date 2025-10-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "../includes/game.h"
#include "../includes/ScreenManager.h"
#include "../includes/player.h"

/**
 * @brief Construct a new Game:: Game object
 *
 */

    Game::Game()
    {

    }
    Game::Game(sf::RenderWindow& win, ScreenManager& sm)
    {

    }
    Game::~Game()
    {

    }
    void Game::handleInput(sf::RectangleShape& playrect, Player obj)
    {
        bool playerMoving = true;
        while(playerMoving)
        {
            obj.movePlayer(playrect);

        }
    }
    void Game::update(float time)
    {
        
    }
    void Game::render()
    {
       
        
    }
    bool Game::isDone() const
    {

    }
    void Game::initializeGame()
    {
        Player player; // Initialize the player object
        sf::RectangleShape playerShape; // Initialize player shape
        sf::Texture playerTexture; // Initialize player texture
        playerTexture.loadFromFile("../assets/HqCreature.png"); // Load player image
        player.startPlayer(playerShape,playerTexture); // This essentially loads both the player shape and texture together
        
        
    }
    /*
        void startPlayer(sf::RectangleShape& rectangle, sf::Texture& playerTexture);
        void movePlayer(sf::RectangleShape &playerRectangle);
        bool boundsChecking(int x, int y);
        void playerShoot(sf::RectangleShape& playerRect,sf::RectangleShape& bulletShape ,sf::Texture& bulletTexture,Bullet &projectile);
        std::vector<sf::RectangleShape> bullets; 
    */

 



