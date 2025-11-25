// #ifndef SCREEN_MANAGER_H
// #define SCREEN_MANAGER_H
//
// #include <SFML/Graphics.hpp>
// #include "button.h"
// #include "Game_State.h"
// #include <vector>
// #include <string>
//
// class ScreenManager {
// private:
//     sf::RenderWindow& window;
//     GameState currentState;
//
//     // UI Elements
//     sf::Font font;
//     sf::Text titleText;
//     sf::Text subtitleText;
//     sf::Text infoText;
//
//     // Buttons for each screen
//     // Main Menu
//     Button* startButton;
//     Button* leaderboardButton;
//     Button* settingsButton;
//     Button* quitButton;
//
//     // Pause Menu (in gameplay)
//     Button* resumeButton;
//     Button* mainMenuButton;
//     Button* quitFromPauseButton;
//
//     // Settings
//     Button* backButton;
//     Button* livesUpButton;
//     Button* livesDownButton;
//     Button* levelUpButton;
//     Button* levelDownButton;
//     std::vector<Button*> playerIconButtons;
//
//     // Game Over
//     Button* playAgainButton;
//     Button* mainMenuFromGameOverButton;
//
//     // Quit Confirmation Dialog
//     Button* confirmYesButton;
//     Button* confirmNoButton;
//     bool showQuitConfirmation;
//
//     // Settings values
//     int lives;
//     int spawnLevel;
//     int selectedPlayerIcon;
//
//     // Leaderboard data
//     struct LeaderboardEntry {
//         std::string name;
//         int score;
//     };
//     std::vector<LeaderboardEntry> leaderboard;
//
//     // Background elements
//     sf::RectangleShape background;
//     sf::RectangleShape dialogOverlay;
//
// public:
//     // Constructor
//     ScreenManager(sf::RenderWindow& win);
//     ~ScreenManager();
//
//     // Initialize all UI elements
//     void initialize();
//
//     // Update based on current state
//     void update(sf::Event& event);
//
//     // Render based on current state
//     void render();
//
//     // State management
//     void setState(GameState newState);
//     GameState getState() const;
//
//     // Settings getters
//     int getLives() const { return lives; }
//     int getSpawnLevel() const { return spawnLevel; }
//     int getSelectedPlayerIcon() const { return selectedPlayerIcon; }
//
//     // Leaderboard management
//     void addScore(const std::string& name, int score);
//     void loadLeaderboard();
//     void saveLeaderboard();
//
// private:
//     // Screen rendering methods
//     void renderMainMenu();
//     void renderPauseMenu();
//     void renderSettings();
//     void renderLeaderboard();
//     void renderGameOver(int finalScore);
//     void renderQuitConfirmation();
//
//     // Button creation helpers
//     void createMainMenuButtons();
//     void createPauseMenuButtons();
//     void createSettingsButtons();
//     void createGameOverButtons();
//     void createQuitConfirmButtons();
//
//     // Cleanup methods
//     void deleteMainMenuButtons();
//     void deletePauseMenuButtons();
//     void deleteSettingsButtons();
//     void deleteGameOverButtons();
//     void deleteQuitConfirmButtons();
//     void deleteAllButtons();
//
//     // Load resources
//     void loadResources();
// };
//
// #endif

/**
 * @file ScreenManager.h
 * @author Ian Codding II
 * @brief Manages which screen is currently active - coordinates screen transitions
 * @version 2.0
 * @date 2025-10-27
 * 
 * @copyright Copyright (c) 2025
 */

#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include <SFML/Graphics.hpp>
#include "Game_State.h"
#include "Screen.h"
#include <map>

/**
 * @class ScreenManager
 * @brief Manages screen transitions and holds the current active screen
 * 
 * This class is now MUCH simpler than before. It only does a few things:
 * 1. Loads and stores the shared font
 * 2. Holds a pointer to the current screen
 * 3. Creates screens on demand (lazy initialization)
 * 4. Forwards update/render calls to the current screen
 * 5. Handles state transitions (switching between screens)
 * 
 * All the button logic, rendering details, and screen-specific behavior
 * is now in individual Screen classes. ScreenManager is just a coordinator.
 * 
 * This is called the "Strategy Pattern" - ScreenManager delegates work
 * to the appropriate Screen object rather than doing it all itself.
 */
class ScreenManager {
private:
    sf::RenderWindow& window;        // Reference to the main window (created in main.cpp)
    sf::Font font;                   // Shared font used by all screens
    
    GameState currentState;          // What state we're currently in
    Screen* currentScreen;           // Pointer to the active screen object
    
    /**
     * Map of all created screens
     * Key: GameState (which state this screen is for)
     * Value: Screen* (pointer to the screen object)
     * 
     * We use a map for "lazy initialization" - screens are only created when first needed.
     * Once created, they're stored here and reused when we return to that state.
     * 
     * Example: If we go MENU -> SETTINGS -> MENU, the MainMenuScreen is reused
     * instead of being deleted and recreated.
     */
    std::map<GameState, Screen*> screens;
    
public:
    /**
     * @brief Constructor - sets up initial state
     * 
     * Takes a reference to the window so all screens draw to the same window.
     * Initializes pointers to nullptr for safety.
     * 
     * @param win Reference to the main SFML window
     */
    ScreenManager(sf::RenderWindow& win);
    
    /**
     * @brief Destructor - cleans up all screens
     * 
     * Iterates through the screens map and deletes each screen to prevent memory leaks.
     * This is called automatically when ScreenManager is destroyed (program ends).
     */
    ~ScreenManager();
    
    /**
     * @brief Initialize - load font and create first screen
     * 
     * Loads the shared font that all screens will use.
     * Creates and initializes the initial screen (main menu).
     * 
     * This must be called after the constructor, once the OpenGL context is ready.
     */
    void initialize();
    
    /**
     * @brief Update - forward event to current screen and handle state changes
     * 
     * Called every frame for each event.
     * Forwards the event to the current screen's update() method.
     * If the screen returns a different state, switches to that screen.
     * 
     * @param event The SFML event to process (mouse click, key press, etc.)
     */
    void update(sf::Event& event);
    
    /**
     * @brief Render - forward to current screen
     * 
     * Called every frame to draw the UI.
     * Simply forwards to the current screen's render() method.
     * Each screen knows how to draw itself.
     */
    void render();
    
    /**
     * @brief Get current state
     * 
     * Returns the current GameState enum value.
     * Useful for main.cpp to determine whether to render game or UI.
     * 
     * @return Current GameState
     */
    GameState getState() const { return currentState; }
    
    /**
     * @brief Set state - switch to different screen
     * 
     * Cleanups the current screen, changes state, gets/creates new screen, initializes it.
     * This is the heart of the state machine - it transitions between states.
     * 
     * @param newState State to transition to
     */
    void setState(GameState newState);
    
    /**
     * @brief Get the shared font
     * 
     * Allows screens or other classes to access the loaded font.
     * 
     * @return Reference to the shared font
     */
    sf::Font& getFont() { return font; }
    
private:
    /**
     * @brief Get or create a screen for the given state
     * 
     * Checks if we've already created a screen for this state.
     * If yes: return the existing screen (reuse it)
     * If no: create new screen, store in map, return it
     * 
     * This is "lazy initialization" - only create screens when needed.
     * Saves memory and startup time.
     * 
     * @param state The state to get screen for
     * @return Pointer to the screen, or nullptr if state not implemented yet
     */
    Screen* getScreen(GameState state);
};

#endif // SCREEN_MANAGER_H