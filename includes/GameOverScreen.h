/**
 * @file GameOverScreen.h
 * @author Ian Codding II
 * @brief Game over screen with name input for top scores
 * @version 1.1
 * @date 2025-12-01
 */

#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include "Screen.h"
#include "button.h"
#include <string>

/**
 * @class GameOverScreen
 * @brief Handles the game over screen displayed when player loses
 */
class GameOverScreen : public Screen {
private:
    Button* playAgainButton;
    Button* mainMenuButton;
    Button* submitButton;
    
    int finalScore;
    bool isTopScore;
    std::string playerName;
    
    sf::Text gameOverText;
    sf::Text scoreText;
    sf::Text namePromptText;
    sf::Text nameDisplayText;
    sf::RectangleShape background;
    sf::RectangleShape nameInputBox;
    
public:
    GameOverScreen(sf::RenderWindow& win, sf::Font& fnt);
    ~GameOverScreen();

    void setScore(int score);
    void setIsTopScore(bool topScore);
    int getScore() const { return finalScore; }

    void initialize() override;
    GameState update(sf::Event& event) override;
    void render() override;
    void cleanup() override;
};

#endif