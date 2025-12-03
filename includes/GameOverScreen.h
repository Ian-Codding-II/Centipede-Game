/**
 * @file GameOverScreen.h
 * @author Ian Codding II
 * @brief Game over screen with name input for top 10 scores
 * @version 1.3 - Fixed member initialization order
 * @date 2025-12-03
 * @copyright Copyright (c) 2025
 */

#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include "Screen.h"
#include "button.h"
#include "ScreenManager.h"
#include <string>

/**
 * @class GameOverScreen
 * @brief Displays game over with score and name input for top 10.
 */
class GameOverScreen : public Screen {
public:
    GameOverScreen(sf::RenderWindow &win, sf::Font &fnt, ScreenManager &manager);
    ~GameOverScreen();

    void initialize() override;
    GameState update(sf::Event &event) override;
    void render() override;
    void cleanup() override;

    void setScore(int score);
    void setIsTopScore(bool topScore);
    std::string getPlayerName() const;
    void reset();

private:
    ScreenManager &screenManager;

    Button *playAgainButton;
    Button *mainMenuButton;
    Button *submitButton;

    sf::RectangleShape background;
    sf::RectangleShape nameInputBox;

    sf::Text gameOverText;
    sf::Text scoreText;
    sf::Text namePromptText;
    sf::Text nameDisplayText;

    int finalScore;
    bool isTopScore;
    std::string playerName;
};

#endif