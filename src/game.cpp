/**
 * @file game.cpp
 * @author Ian Codding II
 * @brief Implementation of Game class - main gameplay logic
 * @version 0.1
 * @date 2025-10-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../includes/game.h"
#include "../includes/errorHandler.h"
#include "../includes/ScreenManager.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

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
    

 




Game::Game(sf::RenderWindow &win, ScreenManager &screenMngr)
    : window(win)
    , screenManager(screenMngr)
    , currentState(GameState::PLAYING)
    , isGameOver(false)
    , isPaused(false)
    , score(0)
    , lives(3)
    , level(1)
    , player(nullptr)
    , centipede(nullptr) {

    std::cout << "[Game] Constructor called\n";

    // ===== SET UP TEXT DISPLAYS =====
    // IMPORTANT: Get the font from ScreenManager (shared font loaded there)
    sf::Font &font = screenManager.getFont();

    // Set up the black background
    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color::Black);

    // Set up score text
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::Green);
    scoreText.setPosition(10, 10);

    // Set up lives text
    livesText.setFont(font);
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::Green);
    livesText.setPosition(window.getSize().x - 200, 10);

    // Set up level text
    levelText.setFont(font);
    levelText.setCharacterSize(20);
    levelText.setFillColor(sf::Color::Green);
    levelText.setPosition(window.getSize().x / 2 - 50, 10);

    std::cout << "[Game] Game object fully initialized\n";
}

Game::~Game() {
}

void Game::initualize() {
}

void Game::handleInput(const sf::Event &event) {
}

void Game::update(float dt) {
}

void Game::render() {
    // ===== DRAW BACKGROUND =====
    // Black rectangle covering entire screen
    window.draw(background);
    // This will be at the top.

    // There will be more to draw, but this will be at the bottom
    // ===== DRAW UI TEXT =====
    // Update and draw score text
    scoreText.setString("Score: " + std::to_string(score));
    window.draw(scoreText);

    // Update and draw lives text
    livesText.setString("Lives: " + std::to_string(lives));
    window.draw(livesText);

    // Update and draw level text
    levelText.setString("Level: " + std::to_string(level));
    window.draw(levelText);
}

/**
 * @brief Get the current game state
 *
 * Returns the current GameState enum value.
 * Used by main.cpp to determine whether to render game or UI.
 *
 * @return Current GameState (PLAYING, PAUSED, GAME_OVER, etc.)
 */
GameState Game::getState() const {
    return currentState;
}

void Game::cleanup() {
}

bool Game::checkCollision() {
}

void Game::addScore() {
}

bool Game::loseLife() {
}

void Game::completLevel() {
}

bool Game::damageCentipedeSegment(int segmentIndex) {
}

void Game::resetAfterDeath() {
}