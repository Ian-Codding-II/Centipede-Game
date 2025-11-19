/**
 * @file MainMenuScreen.h
 * @author Ian Codding II
 * @brief Main menu screen - first screen player sees
 * @version 1.0
 * @date 2025-10-27
 * 
 * @copyright Copyright (c) 2025
 */

#ifndef MAIN_MENU_SCREEN_H
#define MAIN_MENU_SCREEN_H

#include "Screen.h"
#include "button.h"

/**
 * @class MainMenuScreen
 * @brief Handles the main menu interface
 *  
 * It displays:
 * - CENTIPEDE title at top (large green text)
 * - Start Game button (transitions to PLAYING state)
 * - Leaderboard button (shows high scores)
 * - Settings button (configure game options)
 * - Quit button (shows confirmation dialog)
 * 
 * When Quit is clicked, a confirmation dialog appears with Yes/No buttons.
 * Yes: Closes the program
 * No: Cancels and returns to menu
 * 
 * This class is responsible for:
 * - Creating all its buttons
 * - Updating button states
 * - Rendering the menu
 * - Handling button clicks
 * - Cleaning up when transitioning away
 */
class MainMenuScreen : public Screen {
private:
    // Main menu buttons
    Button* startButton;         // "Start Game" - begins gameplay
    Button* leaderboardButton;   // "Leaderboard" - shows high scores
    Button* settingsButton;      // "Settings" - configure options
    Button* quitButton;          // "Quit" - exit program (with confirmation)
    
    // Quit confirmation dialog buttons
    Button* confirmYesButton;    // "Yes" - confirm quit
    Button* confirmNoButton;     // "No" - cancel quit
    bool showQuitDialog;         // Whether dialog is currently showing
    
    // UI text elements
    sf::Text titleText;          // "CENTIPEDE" title
    sf::Text subtitleText;       // Used for dialog text
    
    // Background elements
    sf::RectangleShape background;      // Black background covering screen
    sf::RectangleShape dialogOverlay;   // Semi-transparent overlay for dialog
    
public:
    /**
     * @brief Constructor - sets up initial state
     * 
     * Initializes all pointers to nullptr and sets up background/text objects.
     * Actual button creation happens in initialize().
     * 
     * @param win Reference to main window
     * @param fnt Reference to loaded font
     */
    MainMenuScreen(sf::RenderWindow& win, sf::Font& fnt);
    
    /**
     * @brief Destructor - ensures cleanup is called
     */
    ~MainMenuScreen();
    
    /**
     * @brief Initialize - create all buttons for this screen
     * 
     * Creates the 4 main menu buttons and 2 confirmation dialog buttons.
     * Called once when screen becomes active.
     */
    void initialize() override;
    
    /**
     * @brief Update - process events and return next state
     * 
     * Updates all buttons and checks for clicks.
     * Returns appropriate state based on which button was clicked:
     * - Start Game → PLAYING
     * - Leaderboard → LEADERBOARD
     * - Settings → SETTINGS
     * - Quit (Yes) → closes window
     * - Quit (No) → stays in MENU
     * 
     * @param event The SFML event to process
     * @return Next state to transition to
     */
    GameState update(sf::Event& event) override;
    
    /**
     * @brief Render - draw the main menu
     * 
     * Draws background, title, all buttons, and quit dialog if showing.
     */
    void render() override;
    
    /**
     * @brief Cleanup - delete all buttons
     * 
     * Frees memory used by all buttons.
     * Called when transitioning away from this screen.
     */
    void cleanup() override;
    
private:
    /**
     * @brief Render the quit confirmation dialog
     * 
     * Draws overlay, dialog box, text, and Yes/No buttons.
     * Only called when showQuitDialog is true.
     */
    void renderQuitDialog();
};

#endif // MAIN_MENU_SCREEN_H