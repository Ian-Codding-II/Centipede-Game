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
#include <fstream>
/**
 * @brief Construct a new Game:: Game object
 *
 */

 
    
    Game::Game(sf::RenderWindow& win, ScreenManager& sm) : window(win) 
    {
        initializeGame();
    }
    void Game::handleInput(sf::RectangleShape& playrect, Player* obj)
    {
        
        obj->movePlayer(playrect);
        obj->playerShoot(playrect,bulletShape,bulletTexture,bullet);

    }
    void Game::update(float time)
    { 
        sf::Vector2f position = bulletShape.getPosition();
        float speed = 300.f;           
        position.y -= speed * time;      
        bulletShape.setPosition(position);
        if(position.y <= 5)
        {
            // Delete the bullet object.
        }

    }
    void Game::render()
    {
       window.draw(playerShape);
       window.draw(bulletShape);
    }
    bool Game::isDone() const
    {
        return true;
    }
    void Game::initializeGame()
    {


        player.startPlayer(playerShape,playerTexture); // This essentially loads both the player shape and texture together
        bullet.startBullet(bulletShape,bulletTexture);
        
        
    }
    /*
        void startPlayer(sf::RectangleShape& rectangle, sf::Texture& playerTexture);
        void movePlayer(sf::RectangleShape &playerRectangle);
        bool boundsChecking(int x, int y);
        void playerShoot(sf::RectangleShape& playerRect,sf::RectangleShape& bulletShape ,sf::Texture& bulletTexture,Bullet &projectile);
        std::vector<sf::RectangleShape> bullets; 
        */
    

 



