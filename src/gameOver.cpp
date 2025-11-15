/**
 * @file GameOverScreen.cpp
 * @author Ian Codding II
 * @brief Implementation of GameOverScreen - game over screen
 * @version 1.0
 * @date 2025-10-27
 * 
 * @copyright Copyright (c) 2025
 */

#include "../includes/GameOverScreen.h"
#include "../includes/errorHandler.h"
#include <iostream>
#include <string>

/**
 * @brief Constructor - initialize the game over screen
 * 
 * Sets up:
 * - All button pointers to nullptr
 * - finalScore to 0 (will be set by setScore() before display)
 * - Black background
 * - "GAME OVER" title text (red)
 * - Score display text
 * 
 * @param win Reference to the main window
 * @param fnt Reference to the shared font
 */
GameOverScreen::GameOverScreen(sf::RenderWindow& win, sf::Font& fnt)
    : Screen(win, fnt),
      playAgainButton(nullptr),
      mainMenuButton(nullptr),
      finalScore(0) {
    
    std::cout << "[GameOverScreen] Constructor called" << std::endl;
    
    // Set up the black background
    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color::Black);
    
    // Set up the "GAME OVER" title
    // Red text to indicate failure/end
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(
        (window.getSize().x - gameOverText.getLocalBounds().width) / 2,
        50
    );
    
    // Set up the score display text
    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::Yellow);
    // Position will be updated when score is set
}

/**
 * @brief Destructor - clean up resources
 */
GameOverScreen::~GameOverScreen() {
    std::cout << "[GameOverScreen] Destructor called" << std::endl;
    cleanup();
}

/**
 * @brief Set the final score to display
 * 
 * Updates the finalScore variable and refreshes the score display text.
 * This should be called by the Game class when transitioning to game over.
 * 
 * Example in Game class:
 * ```cpp
 * GameOverScreen* gameOverScreen = (GameOverScreen*)screenManager.getScreen(GameState::GAME_OVER);
 * gameOverScreen->setScore(currentScore);
 * screenManager.setState(GameState::GAME_OVER);
 * ```
 * 
 * @param score The final score to display
 */
void GameOverScreen::setScore(int score) {
    finalScore = score;
    
    // Create the score display string
    // Example: "Final Score: 12500"
    scoreText.setString("Final Score: " + std::to_string(score));
    
    // Center the score text horizontally
    scoreText.setPosition(
        (window.getSize().x - scoreText.getLocalBounds().width) / 2,
        200
    );
    
    std::cout << "[GameOverScreen] Score set to " << score << std::endl;
}

/**
 * @brief Initialize - create all buttons for this screen
 * 
 * Creates 2 buttons:
 * - Play Again button (to start a new game)
 * - Main Menu button (to return to menu)
 * 
 * Button constructor signature:
 * Button(std::string label, sf::Vector2f position, sf::Vector2f size, sf::Color color)
 * 
 * Buttons are positioned below the score display.
 */
void GameOverScreen::initialize() {
    std::cout << "[GameOverScreen] initialize() called" << std::endl;
    
    float winWidth = window.getSize().x;
    float winHeight = window.getSize().y;
    
    // Button dimensions
    float buttonWidth = 200;
    float buttonHeight = 50;
    float spacing = 20;
    
    // Center buttons horizontally
    float centerX = (winWidth - buttonWidth) / 2;
    
    // Calculate vertical position (below score)
    float startY = 300;
    
    // Create PLAY AGAIN button
    // This restarts the game
    playAgainButton = new Button(
        "Play Again",
        sf::Vector2f(centerX, startY),
        sf::Vector2f(buttonWidth, buttonHeight),
        sf::Color::Green
    );
    playAgainButton->setColorTextNormal(sf::Color::Black);
    playAgainButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[GameOverScreen] Created Play Again button" << std::endl;
    
    // Create MAIN MENU button
    // This returns to the main menu
    mainMenuButton = new Button(
        "Main Menu",
        sf::Vector2f(centerX, startY + (buttonHeight + spacing)),
        sf::Vector2f(buttonWidth, buttonHeight),
        sf::Color::Yellow
    );
    mainMenuButton->setColorTextNormal(sf::Color::Black);
    mainMenuButton->setColorTextHover(sf::Color::Green);
    std::cout << "[GameOverScreen] Created Main Menu button" << std::endl;
}

/**
 * @brief Update - process events and return next state
 * 
 * Updates all buttons and handles clicks.
 * 
 * Note: Button::update() takes (sf::Event&, sf::RenderWindow&)
 * Note: Button::getState() returns: normal, hovered, or clicked
 * 
 * Return states:
 * - PLAYING: Play Again clicked - start new game
 * - MENU: Main Menu clicked - return to menu
 * - GAME_OVER: No button clicked - stay on game over screen
 * 
 * @param event The SFML event to process
 * @return Next state to transition to
 */
GameState GameOverScreen::update(sf::Event& event) {
    // Update PLAY AGAIN button
    if (playAgainButton != nullptr) {
        playAgainButton->update(event, window);
        if (playAgainButton->getState() == clicked) {
            std::cout << "[GameOverScreen] Play Again clicked - starting new game" << std::endl;
            return GameState::PLAYING;
        }
    }
    
    // Update MAIN MENU button
    if (mainMenuButton != nullptr) {
        mainMenuButton->update(event, window);
        if (mainMenuButton->getState() == clicked) {
            std::cout << "[GameOverScreen] Main Menu clicked - returning to menu" << std::endl;
            return GameState::MENU;
        }
    }
    
    // No button clicked, stay on game over screen
    return GameState::GAME_OVER;
}

/**
 * @brief Render - draw the game over screen
 * 
 * Drawing order:
 * 1. Black background
 * 2. "GAME OVER" title
 * 3. Final score display
 * 4. Buttons
 */
void GameOverScreen::render() {
    // Draw background
    window.draw(background);
    
    // Draw title
    window.draw(gameOverText);
    
    // Draw score
    window.draw(scoreText);
    
    // Draw buttons
    if (playAgainButton != nullptr) {
        window.draw(*playAgainButton);
    }
    if (mainMenuButton != nullptr) {
        window.draw(*mainMenuButton);
    }
}

/**
 * @brief Cleanup - delete all buttons
 * 
 * Called when transitioning away from this screen.
 * Properly deletes all allocated buttons.
 */
void GameOverScreen::cleanup() {
    std::cout << "[GameOverScreen] cleanup() called" << std::endl;
    
    if (playAgainButton != nullptr) {
        delete playAgainButton;
        playAgainButton = nullptr;
    }
    
    if (mainMenuButton != nullptr) {
        delete mainMenuButton;
        mainMenuButton = nullptr;
    }
    
    std::cout << "[GameOverScreen] All buttons deleted" << std::endl;
}