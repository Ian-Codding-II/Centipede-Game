/**
 * @file GameOverScreen.h
 * @author Ian Codding II
 * @brief Game over screen - displayed when player loses all lives
 * @version 1.0
 * @date 2025-10-27
 * 
 * @copyright Copyright (c) 2025
 */

#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include "Screen.h"
#include "button.h"

/**
 * @class GameOverScreen
 * @brief Handles the game over screen displayed when player loses
 * 
 * This screen appears when the player loses all their lives during gameplay.
 * It displays:
 * - "GAME OVER" title
 * - Final score
 * - Play Again button (start new game)
 * - Main Menu button (return to menu)
 * 
 * The score should be passed to this screen so it can display the final score.
 * In a full implementation, this could also:
 * - Check if score is in top 10 for leaderboard
 * - Allow player to enter name for leaderboard
 * - Show time played, level reached, etc.
 * 
 * Layout:
 * - "GAME OVER" title (large, red)
 * - Final Score: XXXX
 * - Play Again button (green)
 * - Main Menu button (yellow)
 * 
 * This class is responsible for:
 * - Creating game over buttons
 * - Displaying the final score
 * - Updating button states
 * - Rendering the game over screen
 * - Handling button clicks
 * - Cleaning up when transitioning away
 */
class GameOverScreen : public Screen {
private:
    // Game over buttons
    Button* playAgainButton;        // "Play Again" - start new game
    Button* mainMenuButton;         // "Main Menu" - return to menu
    
    // Display information
    int finalScore;                 // The score to display (passed from Game class)
    
    // UI text elements
    sf::Text gameOverText;          // "GAME OVER" title
    sf::Text scoreText;             // "Final Score: XXXX"
    
    // Background
    sf::RectangleShape background;  // Black background
    
public:
    /**
     * @brief Constructor - sets up initial state
     * 
     * Initializes pointers to nullptr and prepares text elements.
     * Button creation happens in initialize().
     * 
     * Note: finalScore is set to 0 initially. It should be updated
     * by calling setScore() before the screen is displayed.
     * 
     * @param win Reference to main window
     * @param fnt Reference to loaded font
     */
    GameOverScreen(sf::RenderWindow& win, sf::Font& fnt);
    
    /**
     * @brief Destructor - ensures cleanup is called
     */
    ~GameOverScreen();
    
    /**
     * @brief Set the final score to display
     * 
     * Called by ScreenManager or Game class before showing this screen.
     * This allows the same GameOverScreen to be reused with different scores.
     * 
     * @param score The final score the player achieved
     */
    void setScore(int score);
    
    /**
     * @brief Get the final score
     * 
     * @return The currently displayed score
     */
    int getScore() const { return finalScore; }
    
    /**
     * @brief Initialize - create all buttons for this screen
     * 
     * Creates the 2 game over buttons.
     * Called once when screen becomes active.
     */
    void initialize() override;
    
    /**
     * @brief Update - process events and return next state
     * 
     * Updates all buttons and checks for clicks.
     * Returns appropriate state based on which button was clicked:
     * - Play Again → PLAYING (new game starts)
     * - Main Menu → MENU
     * 
     * @param event The SFML event to process
     * @return Next state to transition to
     */
    GameState update(sf::Event& event) override;
    
    /**
     * @brief Render - draw the game over screen
     * 
     * Draws background, title, score, and buttons.
     */
    void render() override;
    
    /**
     * @brief Cleanup - delete all buttons
     * 
     * Frees memory used by all buttons.
     * Called when transitioning away from this screen.
     */
    void cleanup() override;
};

#endif // GAME_OVER_SCREEN_H