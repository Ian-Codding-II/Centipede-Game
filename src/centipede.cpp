/**
 * @file    centipede.cpp
 * @author  Balin Becker
 * @brief   Centipede class definitions
 * @date    2025-10-21
 */

#include "../includes/centipede.h"

VertDirection vertState = VertDirection::down;
HoriDirection horiState = HoriDirection::right;

centipede::centipede(sf::Texture& Texture, int length, sf::Vector2f position, sf::Vector2i factor) {
    mLength = length;
    mSpacing = 15;
    mPosition = position;
    
    for (int i = 0; i < length; i++) {
        if (i == 0) {
            // Create a head
            anim_obj* headSeg = new anim_obj(Texture, sf::IntRect(0, 8*1, 8, 8), 4, "CentipedeHead");
            segment* head = new segment(headSeg, "Head");
            head->mSprite->setScale(factor);
            head->mSprite->setPosition(mPosition);
            mCentipedeVect.push_back(head);
        } else {
            // Create a segment
            anim_obj* sSegment = new anim_obj(Texture, sf::IntRect(0, 8*0, 8, 8), 4, "CentipedeSegment");
            segment* seg = new segment(sSegment, "Segment");
            seg->mSprite->setScale(factor);
            seg->mSprite->setPosition(sf::Vector2f(mPosition.x - i * mSpacing, mPosition.y));
            mCentipedeVect.push_back(seg);
        }
    }
    
    vertState = VertDirection::down;
    horiState = HoriDirection::right;
}

/**
 * @brief Places all centipede segments at position
 * 
 * @param position Position to place at
 */
void centipede::setPosition(sf::Vector2f position) {
    for (segment* seg : mCentipedeVect) {
        seg->mSprite->setPosition(position);
    }
}

/**
 * @brief Sets scale of centipede
 * 
 * @param factor Factor to scale by
 */
void centipede::setScale(sf::Vector2i factor) {
    for (segment* seg : mCentipedeVect) {
        seg->mSprite->setScale(factor);
    }
}

/**
 * @brief Moves the centipede to the position
 * 
 * @param position Position to move to
 */
void centipede::move(float dt) {
    elapsedTime += dt;

    if (elapsedTime >= speed) {
        elapsedTime -= speed;

        bool bumped = false;
        sf::Vector2f hPos = mCentipedeVect[0]->mSprite->getSprite().getGlobalBounds().getPosition();
        sf::Vector2f hSize = mCentipedeVect[0]->mSprite->getSprite().getGlobalBounds().getSize();

        int lookDir = 0;
        if (horiState == HoriDirection::left) {
            lookDir = -16;
        } else if (horiState == HoriDirection::right) {
            lookDir = 16;
        }

        std::vector<c_obj*> collisions = mCentipedeVect[0]->mSprite->getCollided(sf::FloatRect(hPos.x + lookDir, hPos.y, hSize.x / 4, hSize.y));
        for (long unsigned int i = 0; i < collisions.size(); i++) {
            if (collisions[i]->getName() == "Mushroom") {
                bumped = true;
                break;
            }
        }

        if (bumped) {
            if (vertState == VertDirection::down) {
                sf::Vector2f prevPos = sf::Vector2f(mCentipedeVect[0]->mSprite->getPosition().x, mCentipedeVect[0]->mSprite->getPosition().y);
                mCentipedeVect[0]->mSprite->setPosition(sf::Vector2f(mCentipedeVect[0]->mSprite->getPosition().x, mCentipedeVect[0]->mSprite->getPosition().y + 16));

                for (int i = 1; i < mLength; i++) {
                    sf::Vector2f currentPos = sf::Vector2f(mCentipedeVect[i]->mSprite->getPosition().x, mCentipedeVect[i]->mSprite->getPosition().y);
                    mCentipedeVect[i]->mSprite->setPosition(prevPos);
                    prevPos = currentPos;
                }

                if (horiState == HoriDirection::left) {
                    horiState = HoriDirection::right;
                } else {
                    horiState = HoriDirection::left;
                }
            
            } else if (vertState == VertDirection::up) {
                sf::Vector2f prevPos = sf::Vector2f(mCentipedeVect[0]->mSprite->getPosition().x, mCentipedeVect[0]->mSprite->getPosition().y);
                mCentipedeVect[0]->mSprite->setPosition(sf::Vector2f(mCentipedeVect[0]->mSprite->getPosition().x, mCentipedeVect[0]->mSprite->getPosition().y - 16));

                for (int i = 1; i < mLength; i++) {
                    sf::Vector2f currentPos = sf::Vector2f(mCentipedeVect[i]->mSprite->getPosition().x - mSpacing, mCentipedeVect[i]->mSprite->getPosition().y);
                    mCentipedeVect[i]->mSprite->setPosition(prevPos);
                    prevPos = currentPos;
                }

                if (horiState == HoriDirection::left) {
                    horiState = HoriDirection::right;
                } else {
                    horiState = HoriDirection::left;
                }
            }
        } else {
            if (horiState == HoriDirection::right) {
                sf::Vector2f prevPos = sf::Vector2f(mCentipedeVect[0]->mSprite->getPosition().x, mCentipedeVect[0]->mSprite->getPosition().y);
                mCentipedeVect[0]->mSprite->setPosition(sf::Vector2f(mCentipedeVect[0]->mSprite->getPosition().x + 16, mCentipedeVect[0]->mSprite->getPosition().y));

                for (int i = 1; i < mLength; i++) {
                    sf::Vector2f currentPos = sf::Vector2f(mCentipedeVect[i]->mSprite->getPosition().x, mCentipedeVect[i]->mSprite->getPosition().y);
                    mCentipedeVect[i]->mSprite->setPosition(prevPos);
                    prevPos = currentPos;
                }
            } else if (horiState == HoriDirection::left) {
                sf::Vector2f prevPos = sf::Vector2f(mCentipedeVect[0]->mSprite->getPosition().x, mCentipedeVect[0]->mSprite->getPosition().y);
                mCentipedeVect[0]->mSprite->setPosition(sf::Vector2f(mCentipedeVect[0]->mSprite->getPosition().x - 16, mCentipedeVect[0]->mSprite->getPosition().y));

                for (int i = 1; i < mLength; i++) {
                    sf::Vector2f currentPos = sf::Vector2f(mCentipedeVect[i]->mSprite->getPosition().x, mCentipedeVect[i]->mSprite->getPosition().y);
                    mCentipedeVect[i]->mSprite->setPosition(prevPos);
                    prevPos = currentPos;
                }
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
        mCentipedeVect[i]->mSprite->update(dt);
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
        target.draw(mCentipedeVect[i]->mSprite->getSprite(), states);
    }
}
