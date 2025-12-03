/**
 * @file    Centipede.h
 * @author  Ian Codding II, Balin Becker
 * @brief   Create a Centipede simulator
 * @date    2025-10-21
 */

// Each segment is its own sprite
// Each segment of the array follows after one another
// Create an (array?) of segments

#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#include "animated_object.h"
#include "grid.h"
#include <vector>
#include <cmath>

enum class HoriDirection {left, right};
enum class VertDirection {up, down};

class Centipede: public sf::Drawable {
public:
    //sf::Texture* mTexture;
    Centipede(sf::Texture& Texture) : Centipede(Texture, 8, sf::Vector2f(0, 0), sf::Vector2i(1, 1)) {};
    Centipede(sf::Texture& Texture, int length, sf::Vector2f position, sf::Vector2i factor);

    ~Centipede();
    // Returns head position
    sf::Vector2f getPosition() {return mPosition;};

    
    void setPosition(sf::Vector2f position);
    
    void setScale(sf::Vector2i factor);
    void move(float dt, Grid grid);
    void fall();
    void hit(const c_obj* part);
    void hit(); // Simple hit
    void update(float dt);
    void draw(sf::RenderTarget& target,sf::RenderStates states) const;

private:
    struct segment {
        segment(anim_obj* sprite, std::string name) {
            mName = name;
            mSprite = sprite;
        }
        anim_obj* mSprite;
        std::string mName;
    };

    std::vector<segment*> mCentipedeVect;
    sf::Vector2f mPosition;
    
    int mLength;
    int mSpacing;
    float elapsedTime = 0.0;
    const float speed = 0.1;
    sf::Texture mTexture;
    
};

#endif