/**
 * @file Screen.h
 * @brief Base class for all screens - defines the interface each screen must implement
 * @author Ian Codding II
 * @date 2025-10-27
 * 
 * This is an abstract base class (interface) that every screen inherits from.
 * It ensures all screens have the same basic functions: update, render, and cleanup.
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include "Game_State.h"

/**
 * @class Screen
 * @brief Abstract base class for all game screens
 * 
 * Every screen (MainMenu, Settings, Leaderboard, etc.) inherits from this class.
 * This ensures they all have the same interface and can be managed uniformly.
 * 
 * This uses polymorphism - ScreenManager can hold a Screen* that points to any
 * derived screen type (MainMenuScreen, SettingsScreen, etc.) and call their methods.
 */
class Screen {
protected:
    // Protected members can be accessed by derived classes
    sf::RenderWindow& window;  // Reference to the main window (shared by all screens)
    sf::Font& font;            // Reference to the shared font (loaded once in ScreenManager)
    
public:
    /**
     * @brief Constructor - all screens need window and font references
     * 
     * We pass these by reference so all screens share the same window and font.
     * This saves memory and ensures everyone draws to the same window.
     * 
     * @param win Reference to the main SFML window
     * @param fnt Reference to the loaded font
     */
    Screen(sf::RenderWindow& win, sf::Font& fnt) 
        : window(win), font(fnt) {}
    
    /**
     * @brief Virtual destructor - ensures proper cleanup of derived classes
     * 
     * CRITICAL: Virtual destructor is required for polymorphism.
     * When we delete a Screen*, it needs to call the correct destructor
     * for the actual derived type (MainMenuScreen, etc.).
     * 
     * Without virtual, only Screen's destructor would be called,
     * and derived class resources wouldn't be cleaned up (memory leak!).
     */
    virtual ~Screen() {}
    
    /**
     * @brief Initialize the screen - create buttons, load data, etc.
     * 
     * Called once when the screen is first created or switched to.
     * Each screen implements this to set up its specific UI elements.
     * 
     * This is separate from the constructor because some operations
     * (like creating SFML objects) need the OpenGL context to be ready.
     */
    virtual void initialize() = 0;  // = 0 means "pure virtual" - MUST be implemented by derived class
    
    /**
     * @brief Update the screen based on events
     * 
     * Called every frame for each event (mouse clicks, key presses, etc.)
     * The screen processes the event and returns what state to go to next.
     * 
     * If the returned state is different from current state, ScreenManager
     * will switch to a different screen. If it returns the current state,
     * we stay on this screen.
     * 
     * @param event The SFML event that occurred (mouse move, click, key press, etc.)
     * @return The game state to transition to (or current state to stay)
     */
    virtual GameState update(sf::Event& event) = 0;
    
    /**
     * @brief Render the screen
     * 
     * Called every frame to draw the screen's UI elements.
     * Each screen draws its own buttons, text, backgrounds, and graphics.
     * 
     * Drawing order matters! Things drawn first appear behind things drawn later.
     */
    virtual void render() = 0;
    
    /**
     * @brief Cleanup the screen - delete buttons, free resources
     * 
     * Called when switching away from this screen.
     * Each screen must clean up its own buttons and resources to prevent memory leaks.
     * 
     * This is also called in the destructor to ensure cleanup happens even if
     * we forget to call it manually.
     */
    virtual void cleanup() = 0;
};

#endif