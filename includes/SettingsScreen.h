/**
 * @file SettingsScreen.h
 * @author Ian Codding II
 * @brief Settings screen - configure game options
 * @version 1.0
 */

#ifndef SETTINGS_SCREEN_H
#define SETTINGS_SCREEN_H

#include "Screen.h"
#include "button.h"

/**
 * @class SettingsScreen
 * @brief Handles the settings/configuration interface
 *
 * This screen allows the player to customize game settings:
 * - Number of lives (1-50)
 * - Starting spawn level (0+)
 *
 * Settings are adjusted using +/- buttons.
 * The Back button returns to the main menu.
 */
class SettingsScreen : public Screen {
private:

    // Navigation button
    Button* backButton;           // "Back" - return to main menu
    
    // Lives adjustment buttons
    Button* livesUpButton;        // "+" - increase lives
    Button* livesDownButton;      // "-" - decrease lives
    
    // Spawn level adjustment buttons
    Button* levelUpButton;        // "+" - increase spawn level
    Button* levelDownButton;      // "-" - decrease spawn level
    
    // Settings values
    int lives;                    // Number of lives
    int spawnLevel;               // Starting level
    
    // UI text elements
    sf::Text titleText;           // "SETTINGS" title
    sf::Text infoText;            // Labels and values
    
    // Background
    sf::RectangleShape background;

public:
    /**
     * @brief Constructor
     */
    SettingsScreen(sf::RenderWindow& win, sf::Font& fnt);
    
    /**
     * @brief Destructor
     */
    ~SettingsScreen();
    
    /**
     * @brief Initialize all buttons for this screen
     */
    void initialize() override;
    
    /**
     * @brief Update logic (button clicks, etc.)
     */
    GameState update(sf::Event& event) override;
    
    /**
     * @brief Render all UI elements
     */
    void render() override;
    
    /**
     * @brief Cleanup allocated memory
     */
    void cleanup() override;
    
    // Getters for Game
    int getLives() const { return lives; }
    int getSpawnLevel() const { return spawnLevel; }
};

#endif // SETTINGS_SCREEN_H
