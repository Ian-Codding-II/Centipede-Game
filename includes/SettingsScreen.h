/**
 * @file SettingsScreen.h
 * @author Ian Codding II
 * @brief Settings screen - configure game options
 * @version 1.0
 * @date 2025-10-27
 * 
 * @copyright Copyright (c) 2025
 */

#ifndef SETTINGS_SCREEN_H
#define SETTINGS_SCREEN_H

#include "Screen.h"
#include "button.h"
#include <vector>

/**
 * @class SettingsScreen
 * @brief Handles the settings/configuration interface
 * 
 * This screen allows the player to customize game settings:
 * - Number of lives (1-5)
 * - Starting spawn level (0+)
 * - Player icon selection (choose from 4 icons)
 * 
 * Settings are adjusted using +/- buttons.
 * The Back button returns to the main menu.
 * 
 * Layout:
 * - Title at top: "SETTINGS"
 * - Lives: X  [−] [+]
 * - Spawn Level: X  [−] [+]
 * - Player Icon: [1] [2] [3] [4]  (selected one has yellow border)
 * - Back button at bottom
 * 
 * This class is responsible for:
 * - Creating all settings buttons
 * - Updating settings values
 * - Rendering the settings screen
 * - Handling button clicks
 * - Cleaning up when transitioning away
 */
class SettingsScreen : public Screen {
private:
    // Navigation button
    Button* backButton;           // "Back" - return to main menu
    
    // Lives adjustment buttons
    Button* livesUpButton;        // "+" - increase lives
    Button* livesDownButton;      // "−" - decrease lives
    
    // Spawn level adjustment buttons
    Button* levelUpButton;        // "+" - increase spawn level
    Button* levelDownButton;      // "−" - decrease spawn level
    
    // Player icon selection buttons
    std::vector<Button*> playerIconButtons;  // 4 buttons numbered 1-4
    
    // Settings values
    int lives;                    // Number of lives (1-5)
    int spawnLevel;              // Starting level (0+)
    int selectedPlayerIcon;      // Which icon is selected (0-3)
    
    // UI text elements
    sf::Text titleText;          // "SETTINGS" title
    sf::Text infoText;           // Used for labels and values
    
    // Background
    sf::RectangleShape background;     // Black background
    
public:
    /**
     * @brief Constructor - sets up initial state
     * 
     * Initializes all pointers to nullptr and sets default settings values.
     * Actual button creation happens in initialize().
     * 
     * @param win Reference to main window
     * @param fnt Reference to loaded font
     */
    SettingsScreen(sf::RenderWindow& win, sf::Font& fnt);
    
    /**
     * @brief Destructor - ensures cleanup is called
     */
    ~SettingsScreen();
    
    /**
     * @brief Initialize - create all buttons for this screen
     * 
     * Creates:
     * - 4 adjustment buttons (+/− for lives and level)
     * - 4 player icon selection buttons
     * - 1 back button
     * Total: 9 buttons
     */
    void initialize() override;
    
    /**
     * @brief Update - process events and return next state
     * 
     * Updates all buttons and handles:
     * - Lives +/− clicks (adjust within 1-5 range)
     * - Level +/− clicks (adjust within 0+ range)
     * - Icon selection clicks (update selectedPlayerIcon)
     * - Back button click (return to MENU)
     * 
     * @param event The SFML event to process
     * @return Next state to transition to (MENU if Back clicked, SETTINGS otherwise)
     */
    GameState update(sf::Event& event) override;
    
    /**
     * @brief Render - draw the settings screen
     * 
     * Draws:
     * - Background
     * - Title
     * - Settings labels and current values
     * - All buttons
     * - Yellow border around selected player icon
     */
    void render() override;
    
    /**
     * @brief Cleanup - delete all buttons
     * 
     * Frees memory used by all buttons.
     * Called when transitioning away from this screen.
     */
    void cleanup() override;
    
    // Getters for settings values (useful for Game class)
    int getLives() const { return lives; }
    int getSpawnLevel() const { return spawnLevel; }
    int getSelectedPlayerIcon() const { return selectedPlayerIcon; }
};

#endif // SETTINGS_SCREEN_H