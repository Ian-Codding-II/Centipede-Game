/**
 * @file bullet.cpp
 * @author Ian Codding II
 * @brief 
 * @version 0.1
 * @date 2025-10-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "../includes/bullet.h"
#include "../includes/player.h"


void Bullet::startBullet(sf::RectangleShape& bulletObj, sf::Texture& bulletTexture)
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
        std::cout << "Bullet texture loaded successfully." << '\n';
        bulletObj.setTexture(&bulletTexture);
    }
    bulletObj.setOutlineThickness(5.f);
    bulletObj.setPosition(10.f, 20.f);


}

float shootCooldown = 0.1f; // seconds
float timeSinceLastShot = 0.0f;
int Bullet::isShooting(sf::RectangleShape& playerRect, sf::RectangleShape& bulletShape, sf::Texture& bulletTexture, Bullet& projectile, float deltaTime)
{
    
    
        timeSinceLastShot += deltaTime;
        int *vectorSize;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeSinceLastShot >= shootCooldown)
        {
            sf::Vector2f pos = playerRect.getPosition();
            bulletShape.setPosition(pos.x + 9, pos.y);
            projectile.bullets.push_back(bulletShape);
            std::cout << "New bullet created." << '\n';
            timeSinceLastShot = 0.0f;
        }
        for (int i = bullets.size() - 1; i >= 0; i--)
        {
            sf::Vector2f del = bullets[i].getPosition();
            if(del.y <= 5)
            {
                bullets.erase(bullets.begin() + i);
                std::cout << "Bullet deleted #" << i << '\n';
            }
        }
        //return bullets.size();
        
        return bullets.size();

    
    
}
