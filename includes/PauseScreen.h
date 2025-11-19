/**
 * @file PauseScreen.h
 * @author Ian Codding II
 * @brief Pause screen - shown when player pauses during gameplay
 * @version 1.0
 * @date 2025-10-27
 * 
 * @copyright Copyright (c) 2025
 */

#ifndef PAUSE_SCREEN_H
#define PAUSE_SCREEN_H

#include "Screen.h"
#include "button.h"

/**
 * @class PauseScreen
 * @brief Handles the pause menu displayed during gameplay
 * 
 * This screen appears when the player presses ESC or a pause button during gameplay.
 * It displays a semi-transparent overlay over the game and allows the player to:
 * - Resume Game (continue playing)
 * - Main Menu (abandon current game and return to main menu)
 * - Quit (exit program with confirmation)
 * 
 * Layout:
 * - Semi-transparent overlay covering entire screen
 * - "PAUSED" title in center
 * - Resume button (green)
 * - Main Menu button (yellow)
 * - Quit button (red)
 * - Quit confirmation dialog (if Quit is clicked)
 * 
 * This class is responsible for:
 * - Creating pause menu buttons
 * - Updating button states
 * - Rendering the pause overlay
 * - Handling button clicks
 * - Managing quit confirmation
 * - Cleaning up when transitioning away
 */
class PauseScreen : public Screen {
private:
    // Pause menu buttons
    Button* resumeButton;           // "Resume" - continue game
    Button* mainMenuButton;         // "Main Menu" - abandon current game
    Button* quitButton;             // "Quit" - exit program
    
    // Quit confirmation dialog buttons
    Button* confirmYesButton;       // "Yes" - confirm quit
    Button* confirmNoButton;        // "No" - cancel quit
    bool showQuitDialog;            // Whether quit confirmation is showing
    
    // UI text elements
    sf::Text pausedText;            // "PAUSED" title
    sf::Text subtitleText;          // Additional text
    
    // Background/overlay elements
    sf::RectangleShape overlay;     // Semi-transparent overlay over game
    sf::RectangleShape dialogBox;   // Dialog background
    
public:
    /**
     * @brief Constructor - sets up initial state
     * 
     * Initializes all pointers to nullptr and sets up overlay and text objects.
     * Button creation happens in initialize().
     * 
     * @param win Reference to main window
     * @param fnt Reference to loaded font
     */
    PauseScreen(sf::RenderWindow& win, sf::Font& fnt);
    
    /**
     * @brief Destructor - ensures cleanup is called
     */
    ~PauseScreen();
    
    /**
     * @brief Initialize - create all buttons for this screen
     * 
     * Creates the 3 pause menu buttons and 2 confirmation dialog buttons.
     * Called once when screen becomes active.
     */
    void initialize() override;
    
    /**
     * @brief Update - process events and return next state
     * 
     * Updates all buttons and checks for clicks.
     * Returns appropriate state based on which button was clicked:
     * - Resume → PLAYING
     * - Main Menu → MENU
     * - Quit (Yes) → closes window
     * - Quit (No) → stays in PAUSED
     * 
     * @param event The SFML event to process
     * @return Next state to transition to
     */
    GameState update(sf::Event& event) override;
    
    /**
     * @brief Render - draw the pause screen
     * 
     * Draws overlay, title, buttons, and quit dialog if showing.
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
     * Draws dialog box, text, and Yes/No buttons.
     */
    void renderQuitDialog();
};

#endif // PAUSE_SCREEN_H