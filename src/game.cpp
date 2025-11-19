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

/**
 * @brief Construct a new Game:: Game object
 *
 */
Game::Game()
    : mWindow(sf::VideoMode(640, 480), "Bouncing sprite.") {
    mWindow.setFramerateLimit(60);
    mWindow.setPosition({50, 50});
    mTextureTile.loadFromFile("assets/rpg_textures.png");
    mCherryPlant.setRadius(31);
    mCherryPlant.setTexture(&mTextureTile);
    mCherryPlant.setTextureRect(sf::IntRect(64, 32, 62, 62));
    mCherryPlant.setOrigin(62.f / 2.f, 62.f / 2.f);
    mIncrement = sf::Vector2f(4.f, 4.f);
    mIsDone = false;
}


Game::Game(sf::RenderWindow& win, ScreenManager& sm)
{

    




}




/**
 * @brief
 *
 */
void Game::handleInput() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            // Close window button clicked.
            mWindow.close();
        }
    }
}

/**
 * @brief
 *
 */
void Game::update(float time) {
    moveCherry(time);
}

/**
 * @brief
 *
 */
void Game::moveCherry(float time) {
    sf::Vector2u winSize = mWindow.getSize();
    int cherryX = 62;
    int cherryY = 62;
    float speed = 60; // controls speed

    if ((mCherryPlant.getPosition().x + (cherryX / 2) > winSize.x && mIncrement.x > 0) ||
        (mCherryPlant.getPosition().x - (cherryX / 2) < 0 && mIncrement.x < 0)) {
        // Reverse the direction on X axis
        mIncrement.x = -mIncrement.x;
    }
    if ((mCherryPlant.getPosition().y + (cherryY / 2) > winSize.y && mIncrement.y > 0) ||
        (mCherryPlant.getPosition().y - (cherryY / 2) < 0 && mIncrement.y < 0)) {
        // Reverse the direction on Y axis.
        mIncrement.y = -mIncrement.y;
    }
    mCherryPlant.setPosition(
        mCherryPlant.getPosition().x + mIncrement.x*speed*time,
        mCherryPlant.getPosition().y + mIncrement.y*speed*time);
}

/**
 * @brief 
 * 
 */
void Game::render() {
    mWindow.clear(sf::Color::Black);
    mWindow.draw(mCherryPlant);
    mWindow.display();
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool Game::isDone() const {
    return (!mWindow.isOpen() || mIsDone);
}