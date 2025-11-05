/**
 * @file screenManager.cpp
 * @author Ian Codding II
 * @brief Implementation of ScreenManager class
 * @version 0.1
 * @date 2025-10-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "../../includes/screenManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>

// ============================================================================
// RENDERING METHODS
// These draw the UI for each state
// Drawing order matters - things drawn first appear behind things drawn later
// ============================================================================

/**
 * @brief Render the main menu
 * 
 * Draws the CENTIPEDE title at the top and the 4 menu buttons.
 * The title is centered horizontally by subtracting half its width from center.
 */
void ScreenManager::renderMainMenu() {
    // Draw title centered at top
    titleText.setString("CENTIPEDE");
    // Center it: take screen center (400) and subtract half the text width
    titleText.setPosition(400 - titleText.getGlobalBounds().width / 2, 80);
    window.draw(titleText);
    
    // Draw all menu buttons (with safety checks)
    // If a button is nullptr (doesn't exist), skip drawing it
    if (startButton) startButton->draw(window, sf::RenderStates::Default);
    if (leaderboardButton) leaderboardButton->draw(window, sf::RenderStates::Default);
    if (settingsButton) settingsButton->draw(window, sf::RenderStates::Default);
    if (quitButton) quitButton->draw(window, sf::RenderStates::Default);
}

/**
 * @brief Render the pause menu
 * 
 * Shows a dark sidebar on the right with pause controls.
 * The game state (frozen) is rendered in main.cpp before this is called.
 */
void ScreenManager::renderPauseMenu() {
    // Draw semi-transparent sidebar on the right side
    // This provides a background for the pause buttons
    sf::RectangleShape sidebar(sf::Vector2f(200, 600));  // 200 pixels wide, full height
    sidebar.setPosition(600, 0);  // Position at X=600 (right side)
    sidebar.setFillColor(sf::Color(40, 40, 40, 200));  // Dark gray, semi-transparent
    window.draw(sidebar);
    
    // Draw "PAUSED" text at top of sidebar
    infoText.setString("PAUSED");
    infoText.setCharacterSize(30);
    infoText.setPosition(640, 50);  // Centered in sidebar
    window.draw(infoText);
    
    // Draw pause menu buttons
    if (resumeButton) resumeButton->draw(window, sf::RenderStates::Default);
    if (mainMenuButton) mainMenuButton->draw(window, sf::RenderStates::Default);
    if (quitFromPauseButton) quitFromPauseButton->draw(window, sf::RenderStates::Default);
}

/**
 * @brief Render the settings screen
 * 
 * Shows title, current settings values, adjustment buttons, and player icon selection.
 * The selected icon gets a yellow outline box drawn around it.
 */
void ScreenManager::renderSettings() {
    // Draw title
    titleText.setString("SETTINGS");
    titleText.setPosition(400 - titleText.getGlobalBounds().width / 2, 50);
    window.draw(titleText);
    
    // Draw "Lives: X" text
    // The +/- buttons are drawn separately
    infoText.setCharacterSize(25);
    infoText.setString("Lives: " + std::to_string(lives));
    infoText.setPosition(350, 205);
    window.draw(infoText);
    
    // Draw "Spawn Level: X" text
    infoText.setString("Spawn Level: " + std::to_string(spawnLevel));
    infoText.setPosition(320, 265);
    window.draw(infoText);
    
    // Draw "Player Icon:" label
    infoText.setString("Player Icon:");
    infoText.setPosition(330, 320);
    window.draw(infoText);
    
    // Draw adjustment buttons
    if (livesUpButton) livesUpButton->draw(window, sf::RenderStates::Default);
    if (livesDownButton) livesDownButton->draw(window, sf::RenderStates::Default);
    if (levelUpButton) levelUpButton->draw(window, sf::RenderStates::Default);
    if (levelDownButton) levelDownButton->draw(window, sf::RenderStates::Default);
    
    // Draw player icon selection buttons with selection indicator
    for (size_t i = 0; i < playerIconButtons.size(); i++) {
        if (playerIconButtons[i]) {
            // Draw the button
            playerIconButtons[i]->draw(window, sf::RenderStates::Default);
            
            // If this is the selected icon, draw a yellow box around it
            if (i == static_cast<size_t>(selectedPlayerIcon)) {
                sf::RectangleShape selector(sf::Vector2f(70, 70));  // Slightly bigger than button
                selector.setPosition(
                    playerIconButtons[i]->getPosition().x - 35,  // Center it on button
                    playerIconButtons[i]->getPosition().y - 35
                );
                selector.setFillColor(sf::Color::Transparent);  // No fill, just outline
                selector.setOutlineColor(sf::Color::Yellow);    // Yellow outline
                selector.setOutlineThickness(3);                // 3 pixels thick
                window.draw(selector);
            }
        }
    }
    
    // Draw back button at bottom
    if (backButton) backButton->draw(window, sf::RenderStates::Default);
}

/**
 * @brief Render the leaderboard
 * 
 * Shows title and up to 10 high scores.
 * Displays rank number, player name, and score for each entry.
 */
void ScreenManager::renderLeaderboard() {
    // Draw title
    titleText.setString("LEADERBOARD");
    titleText.setPosition(400 - titleText.getGlobalBounds().width / 2, 50);
    window.draw(titleText);
    
    // Draw leaderboard entries
    // Show up to 10 entries, or however many we have (whichever is less)
    infoText.setCharacterSize(22);
    for (size_t i = 0; i < leaderboard.size() && i < 10; i++) {
        // Format: "1. PlayerName - 12345"
        std::string entry = std::to_string(i + 1) + ". " + 
                           leaderboard[i].name + " - " + 
                           std::to_string(leaderboard[i].score);
        infoText.setString(entry);
        infoText.setPosition(250, 150 + i * 35);  // Each entry 35 pixels below previous
        window.draw(infoText);
    }
    
    // Draw instruction to return
    infoText.setCharacterSize(18);
    infoText.setString("Press ESC to return");
    infoText.setPosition(300, 550);
    window.draw(infoText);
}

/**
 * @brief Render the game over screen
 * 
 * Shows semi-transparent overlay, "GAME OVER" text, final score, and buttons.
 * 
 * @param finalScore The player's final score (currently unused, TODO: pass from Game class)
 */
void ScreenManager::renderGameOver(int finalScore) {
    // Draw dark overlay to dim the game behind it
    window.draw(dialogOverlay);
    
    // Draw "GAME OVER" title in red
    titleText.setString("GAME OVER");
    titleText.setFillColor(sf::Color::Red);
    titleText.setPosition(400 - titleText.getGlobalBounds().width / 2, 150);
    window.draw(titleText);
    
    // Draw final score
    subtitleText.setString("Your Score: " + std::to_string(finalScore));
    subtitleText.setPosition(400 - subtitleText.getGlobalBounds().width / 2, 240);
    window.draw(subtitleText);
    
    // Draw high score if we have any scores saved
    if (!leaderboard.empty()) {
        infoText.setString("High Score: " + std::to_string(leaderboard[0].score));
        infoText.setPosition(400 - infoText.getGlobalBounds().width / 2, 280);
        window.draw(infoText);
    }
    
    // Draw buttons
    if (playAgainButton) playAgainButton->draw(window, sf::RenderStates::Default);
    if (mainMenuFromGameOverButton) mainMenuFromGameOverButton->draw(window, sf::RenderStates::Default);
}

/**
 * @brief Render the quit confirmation dialog
 * 
 * Shows a dialog box on top of everything asking "Are you sure you want to quit?"
 * with Yes and No buttons. The background is darkened with a semi-transparent overlay.
 */
void ScreenManager::renderQuitConfirmation() {
    // Draw dark overlay over entire screen
    // This dims everything behind the dialog
    window.draw(dialogOverlay);
    
    // Draw dialog box (a rectangle in the center)
    sf::RectangleShape dialogBox(sf::Vector2f(400, 200));  // 400x200 pixels
    dialogBox.setPosition(200, 200);  // Centered: (800-400)/2 = 200, (600-200)/2 = 200
    dialogBox.setFillColor(sf::Color(50, 50, 50));  // Dark gray
    dialogBox.setOutlineColor(sf::Color::White);    // White border
    dialogBox.setOutlineThickness(3);               // 3 pixel border
    window.draw(dialogBox);
    
    // Draw "Are you sure" text (line 1)
    subtitleText.setString("Are you sure");
    subtitleText.setPosition(400 - subtitleText.getGlobalBounds().width / 2, 230);
    window.draw(subtitleText);
    
    // Draw "you want to quit?" text (line 2)
    subtitleText.setString("you want to quit?");
    subtitleText.setPosition(400 - subtitleText.getGlobalBounds().width / 2, 270);
    window.draw(subtitleText);
    
    // Draw Yes and No buttons
    if (confirmYesButton) confirmYesButton->draw(window, sf::RenderStates::Default);
    if (confirmNoButton) confirmNoButton->draw(window, sf::RenderStates::Default);
}
