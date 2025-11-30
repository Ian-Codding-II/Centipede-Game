/**
 * @file    centipede.h
 * @author  Ian Codding II, Balin Becker
 * @brief   Create a centipede simulator
 * @date    2025-10-21
 */

// Each segment is its own sprite
// Each segment of the array follows after one another
// Create an (array?) of segments

#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#include "animated_object.h"
#include <vector>

class centipede {
public:
    centipede(sf::Texture& Texture) : centipede(Texture, 8, sf::Vector2i(1, 1)) {};
    centipede(sf::Texture& Texture, int length, sf::Vector2i factor);

    void setScale(sf::Vector2i factor);
    void move(sf::Vector2i position);
    void fall();

private:
    struct segment {
        segment(anim_obj& sprite, std::string name) {
            mName = name;
            mSprite = &sprite;
        }
        anim_obj* mSprite;
        std::string mName;
    };

    std::vector<segment> mCentipedeVect;
    int mSpacing;
    
};

#endif