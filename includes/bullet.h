/**
 * @file bullet.h
 * @author Ian Codding II Roman Salazar
 * @brief Bullet class - projectiles fired by player
 * @version 1.1 - Fixed memory management
 * @date 2025-12-03
 * @copyright Copyright (c) 2025
 */

#ifndef BULLET_H
#define BULLET_H

#include "collision_object.h"
#include <SFML/Graphics.hpp>

class Bullet : public c_obj {
public:
    // Default constructor
    Bullet() : alive(false) {}

    // Main constructor - creates real bullets
    Bullet(sf::Texture &bulletTexture, sf::Vector2i startPos, float speed = 600.0f)
        : c_obj(bulletTexture, sf::IntRect(64, 32, 32, 32), 
                sf::Vector2f(startPos.x, startPos.y), "Bullet"),
          alive(true) {
        velocity = sf::Vector2f(0.0f, -speed);
    }

    void kill() { alive = false; }
    
    void update(float dt) {
        if (!alive) return;
        mSprite.move(velocity * dt);
        if (mSprite.getPosition().y < -50.0f) {
            alive = false;
        }
    }

    bool isAlive() const { return alive; }

    // Shooting function
    static void shoot(sf::Vector2f playerPos, float deltaTime, sf::Texture &bulletTex);

    static std::vector<Bullet*> bullets;
    static float timeSinceLastShot;
    static float shootCooldown;

private:
    sf::Vector2f velocity;
    bool alive;
};

#endif