/**
 * @file GameOverScreen.cpp
 * @author Ian Codding II
 * @brief Game over screen with name input for top 10 scores
 * @version 1.1
 * @date 2025-12-01
 */

#include "../includes/GameOverScreen.h"
#include "../includes/errorHandler.h"
#include "../includes/LeaderboardScreen.h"
#include <iostream>
#include <string>

/**
 * @brief Constructor - setup game over screen
 * @param win Reference to render window
 * @param fnt Reference to font
 */
GameOverScreen::GameOverScreen(sf::RenderWindow& win, sf::Font& fnt)
    : Screen(win, fnt),
      playAgainButton(nullptr),
      mainMenuButton(nullptr),
      submitButton(nullptr),
      finalScore(0),
      isTopScore(false),
      playerName("") {
    
    std::cout << "[GameOverScreen] Constructor called" << std::endl;
    
    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color::Black);
    
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(
        (window.getSize().x - gameOverText.getLocalBounds().width) / 2,
        50
    );
    
    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::Yellow);
    
    namePromptText.setFont(font);
    namePromptText.setString("Enter your name for leaderboard (max 16 chars):");
    namePromptText.setCharacterSize(24);
    namePromptText.setFillColor(sf::Color::Green);
    namePromptText.setPosition(50, 280);
    
    nameInputBox.setSize(sf::Vector2f(400, 60));
    nameInputBox.setPosition(350, 330);
    nameInputBox.setFillColor(sf::Color(50, 50, 50));
    nameInputBox.setOutlineThickness(2);
    nameInputBox.setOutlineColor(sf::Color::Green);
    
    nameDisplayText.setFont(font);
    nameDisplayText.setCharacterSize(30);
    nameDisplayText.setFillColor(sf::Color::White);
    nameDisplayText.setPosition(370, 340);
}

/**
 * @brief Destructor - cleanup buttons
 */
GameOverScreen::~GameOverScreen() {
    std::cout << "[GameOverScreen] Destructor called" << std::endl;
    cleanup();
}

/**
 * @brief Set final score to display
 * @param score Final score achieved
 */
void GameOverScreen::setScore(int score) {
    finalScore = score;
    scoreText.setString("Final Score: " + std::to_string(score));
    scoreText.setPosition(
        (window.getSize().x - scoreText.getLocalBounds().width) / 2,
        200
    );
    std::cout << "[GameOverScreen] Score set to " << score << std::endl;
}

/**
 * @brief Mark if score qualifies for top 10
 * Shows name input box if true
 * @param topScore true if top 10 score
 */
void GameOverScreen::setIsTopScore(bool topScore) {
    isTopScore = topScore;
    playerName = "";
    nameDisplayText.setString("");
    std::cout << "[GameOverScreen] isTopScore = " << topScore << std::endl;
}

/**
 * @brief Initialize buttons
 * Shows name input only if isTopScore is true
 */
void GameOverScreen::initialize() {
    std::cout << "[GameOverScreen] initialize() called" << std::endl;
    
    float winWidth = window.getSize().x;
    float winHeight = window.getSize().y;
    
    float buttonWidth = 200;
    float buttonHeight = 50;
    float spacing = 20;
    float centerX = (winWidth - buttonWidth) / 2;
    
    float startY = isTopScore ? 450 : 300;
    
    playAgainButton = new Button(
        "Play Again",
        sf::Vector2f(centerX, startY),
        sf::Vector2f(buttonWidth, buttonHeight),
        sf::Color::Green
    );
    playAgainButton->setColorTextNormal(sf::Color::Black);
    playAgainButton->setColorTextHover(sf::Color::Yellow);
    
    mainMenuButton = new Button(
        "Main Menu",
        sf::Vector2f(centerX, startY + (buttonHeight + spacing)),
        sf::Vector2f(buttonWidth, buttonHeight),
        sf::Color::Yellow
    );
    mainMenuButton->setColorTextNormal(sf::Color::Black);
    mainMenuButton->setColorTextHover(sf::Color::Green);
    
    if (isTopScore) {
        submitButton = new Button(
            "Submit",
            sf::Vector2f(centerX, 410),
            sf::Vector2f(buttonWidth, buttonHeight),
            sf::Color::Cyan
        );
        submitButton->setColorTextNormal(sf::Color::Black);
        submitButton->setColorTextHover(sf::Color::Yellow);
    }
}

/**
 * @brief Update event handling
 * Handles name input (if top score) and button clicks
 * @param event SFML event to process
 */
GameState GameOverScreen::update(sf::Event& event) {
    // Name input handling
    if (isTopScore && event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) {
            char c = static_cast<char>(event.text.unicode);
            
            if (c == '\b') {
                if (!playerName.empty()) {
                    playerName.pop_back();
                }
            } else if (c >= 32 && playerName.length() < 16) {
                playerName += c;
            }
            
            nameDisplayText.setString(playerName);
        }
    }
    
    // Button handling
    if (submitButton && isTopScore) {
        submitButton->update(event, window);
        if (submitButton->getState() == clicked && !playerName.empty()) {
            std::cout << "[GameOverScreen] Name submitted: " << playerName << std::endl;
            isTopScore = false;
            playerName = "";
        }
    }
    
    if (playAgainButton != nullptr) {
        playAgainButton->update(event, window);
        if (playAgainButton->getState() == clicked) {
            std::cout << "[GameOverScreen] Play Again clicked" << std::endl;
            return GameState::PLAYING;
        }
    }
    
    if (mainMenuButton != nullptr) {
        mainMenuButton->update(event, window);
        if (mainMenuButton->getState() == clicked) {
            std::cout << "[GameOverScreen] Main Menu clicked" << std::endl;
            return GameState::MENU;
        }
    }
    
    return GameState::GAME_OVER;
}

/**
 * @brief Render game over screen
 * Shows name input box if isTopScore is true
 */
void GameOverScreen::render() {
    window.draw(background);
    window.draw(gameOverText);
    window.draw(scoreText);
    
    if (isTopScore) {
        window.draw(namePromptText);
        window.draw(nameInputBox);
        window.draw(nameDisplayText);
        
        if (submitButton) {
            window.draw(*submitButton);
        }
    }
    
    if (playAgainButton) {
        window.draw(*playAgainButton);
    }
    if (mainMenuButton) {
        window.draw(*mainMenuButton);
    }
}

/**
 * @brief Clean up all allocated buttons
 */
void GameOverScreen::cleanup() {
    std::cout << "[GameOverScreen] cleanup() called" << std::endl;
    
    if (playAgainButton) {
        delete playAgainButton;
        playAgainButton = nullptr;
    }
    if (mainMenuButton) {
        delete mainMenuButton;
        mainMenuButton = nullptr;
    }
    if (submitButton) {
        delete submitButton;
        submitButton = nullptr;
    }
}