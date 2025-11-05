/**
 * @file player.cpp
 * @author Ian Codding II
 * @brief 
 * @version 0.1
 * @date 2025-10-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../includes/player.h"

void startPlayer(sf::RectangleShape& rectangle, sf::Texture& playerTexture)
{
 // Rectangle for player
    rectangle.setSize(sf::Vector2f(30.f, 30.f));
    rectangle.setOutlineColor(sf::Color::Black);
    //rectangle.setOutlineThickness(5.f); // Do we need this?
    rectangle.setPosition(10.f, 20.f);

    // Load player texture
    if (!playerTexture.loadFromFile("/home/roman/CS151/Final/assets/HqCreature.png"))
    {
        std::cerr << "There was an issue loading the player texture...\n";
    }
    std::cout << "Success loading player texture...\n";

    // Apply texture to rectangle
    rectangle.setTexture(&playerTexture);

    



}
/*
void changeBullet(sf::RectangleShape& bulletObj, sf::Texture& bulletTexture)
{
    bulletObj.setSize(sf::Vector2f(10.f, 10.f));
    bulletObj.setOutlineColor(sf::Color::Black);
    bulletObj.setPosition(10.f, 20.f);

    if (!bulletTexture.loadFromFile("/home/roman/CS151/Final/assets/purpleLaser.png"))
    {
        std::cerr << "There was an issue loading the player texture...\n";
    }
    else
    {
        bulletObj.setTexture(&bulletTexture);
    }
    //bulletObj.setOutlineThickness(5.f);
   // rectangle.setPosition(10.f, 20.f);


}*/
void movePlayer(sf::RectangleShape &playerRectangle)
{
    sf::Vector2f pos = playerRectangle.getPosition();
    std::cout << "The current player position is equal to x: " << pos.x << " and y: " << pos.y << '\n';

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) && boundsChecking(pos.x,pos.y))
    {
        playerRectangle.setPosition(pos.x - 15,pos.y); // Move left 20 pixels
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) && boundsChecking(pos.x,pos.y))
    {
        playerRectangle.setPosition(pos.x + 15,pos.y); // Move right 20 pixels
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) && boundsChecking(pos.x,pos.y))
    {
        playerRectangle.setPosition(pos.x,pos.y + 15); // Move down 20 pixels
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) && boundsChecking(pos.x,pos.y))
    {
        playerRectangle.setPosition(pos.x,pos.y - 15); // Move up 20 pixels
    }
    if(!boundsChecking(pos.x,pos.y))
    {
        playerRectangle.setPosition(400,300);
    }
    
   




}

 bool boundsChecking(int x, int y)
 {
     if(x >= 800 || y >= 600 || x <= 0 || y <= 0)
     {
        return 0;
     }
     return 1;
 }


void playerShoot(const sf::Vector2f &bulletPath, sf::RectangleShape& bulletRectangle, sf::Texture& bulletTexture)
{
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        std::cout << "Shoot..." << '\n';
        bulletRectangle.setPosition(400,300);
        bulletRectangle.setTexture(&bulletTexture);
    }
    

}






