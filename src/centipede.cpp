/**
 * @file    centipede.cpp
 * @author  Balin Becker
 * @brief   Centipede class definitions
 * @date    2025-10-21
 */

#include "../includes/centipede.h"

centipede::centipede(sf::Texture& Texture, int length, sf::Vector2f position, sf::Vector2i factor) {
    mLength = length;
    mSpacing = 15;
    mPosition = position;

    for (int i = 0; i < length; i++) {
        if (i == 0) {
            // Create a head
            anim_obj* headSeg = new anim_obj(Texture, sf::IntRect(0, 8*1, 8, 8), 4, "CentipedeHead") ;
            segment* head = new segment(*headSeg, "Head");
            head->mSprite->setScale(factor);
            head->mSprite->setPosition(mPosition);
            mCentipedeVect.push_back(*head);
        } else {
            // Create a segment
            anim_obj* sSegment = new anim_obj(Texture, sf::IntRect(0, 8*0, 8, 8), 4, "CentipedeSegment");
            segment* seg = new segment(*sSegment, "Segment");
            seg->mSprite->setScale(factor);
            seg->mSprite->setPosition(sf::Vector2f(mPosition.x - i * mSpacing, mPosition.y));
            mCentipedeVect.push_back(*seg);
        }
    }

}

/**
 * @brief Places all centipede segments at position
 * 
 * @param position Position to place at
 */
void centipede::setPosition(sf::Vector2f position) {
    for (segment seg : mCentipedeVect) {
        seg.mSprite->setPosition(position);
    }
}

/**
 * @brief Sets scale of centipede
 * 
 * @param factor Factor to scale by
 */
void centipede::setScale(sf::Vector2i factor) {
    for (segment seg : mCentipedeVect) {
        seg.mSprite->setScale(factor);
    }
}

/**
 * @brief Moves the centipede to the position
 * 
 * @param position Position to move to
 */
void centipede::move() {
    segment* Head = &mCentipedeVect[0];
    for (int i = 0; i < mLength; i++) {
        mCentipedeVect[i].mSprite->setPosition(sf::Vector2f(mCentipedeVect[i].mSprite->getPosition().x + 1, mCentipedeVect[i].mSprite->getPosition().y));
    }
    for (int i = 0; i < mLength; i++) {
        std::vector<c_obj*> vect = (mCentipedeVect[i].mSprite->getCollided());
        for (c_obj* obj: vect) {
            if (obj) {

            }
        }
    }
    
}

/**
 * @brief Causes centipede to fall the ground
 */
void centipede::fall() {

}

/**
 * @brief 
 * 
 */
void centipede::update(float dt) {
    for (int i = 0; i < mLength; i++) {
        mCentipedeVect[i].mSprite->update(dt);
    }
}

/**
 * @brief 
 * 
 * @param target 
 * @param states 
 */
void centipede::draw(sf::RenderTarget& target,sf::RenderStates states) const {
    for (int i = 0; i < mLength; i++) {
        target.draw(mCentipedeVect[i].mSprite->getSprite(), states);
    }
}
