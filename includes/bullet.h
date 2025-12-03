// bullet.h
#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "collision_object.h"

class Bullet : public c_obj
{
public:
    // Default constructor (needed for some containers)
    Bullet() : alive(false) {}

    // Main constructor - this is what creates real bullets
    Bullet(sf::Texture& bulletTexture, sf::Vector2i startPos, float speed = 600.0f)
        : alive(true)
    {
        mTexture = &bulletTexture;
        mSprite.setTexture(bulletTexture);
        mSprite.setTextureRect(sf::IntRect(64, 32, 32, 32));  // Your purple laser in atlas
        mSprite.setPosition(static_cast<float>(startPos.x), static_cast<float>(startPos.y));
        mSprite.setOrigin(16.f, 16.f);  // Center the sprite (32x32)

        velocity = sf::Vector2f(0.0f, -speed);  // MOVE UPWARD
    }

    void update(float dt)
    {
        if (!alive) return;

        mSprite.move(velocity * dt);  // Actually moves now!

        // Remove when off top of screen
        if (mSprite.getPosition().y < -50.0f)
        {
            alive = true;
        }
    }

    bool isAlive() const { return alive; }

    // Shooting function
    static void shoot(sf::Vector2i playerPos, float deltaTime, sf::Texture& bulletTex);

    static std::vector<Bullet*> bullets;

    //float shootCooldown;
    //static float timeSinceLastShot;

private:
    sf::Vector2f velocity;
    bool alive;
};

#endif