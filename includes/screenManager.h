// /**
//  * @file screenManager.h
//  * @author Ian Codding II
//  * @brief Centralized manager for all UI screens, menus, and game state transitions.
//  * @version 0.1
//  * @date 2025-10-26
//  * 
//  * @copyright Copyright (c) 2025
//  * 
//  */
//
// #ifndef SCREEN_MANAGER_H
// #define SCREEN_MANAGER_H
//
// #include <SFML/Graphics.hpp>
// #include <memory>
// #include <vector>
// #include <unordered_map>
// #include <string>
//
// #include "button.h"
// #include "Game_State.h"
//
// class ScreenManager {
// public:
//     explicit ScreenManager(sf::RenderWindow& win);
//     ~ScreenManager();
//
//     /** Initialize all UI elements and default settings. */
//     void initialize();
//
//     /** Process input events (keyboard, mouse, etc.). */
//     void update(sf::Event& event);
//
//     /** Draws the current screen and all active UI elements. */
//     void render();
//
//     /** Change the active screen. */
//     void setState(GameState newState);
//
//     /** Get the currently active screen/state. */
//     GameState getState() const { return currentState; }
//
//     // ---------------------------
//     // Settings + Data Accessors
//     // ---------------------------
//     int getLives() const { return lives; }
//     int getSpawnLevel() const { return spawnLevel; }
//     int getSelectedPlayerIcon() const { return selectedPlayerIcon; }
//
//     void addScore(const std::string& name, int score);
//     void loadLeaderboard();
//     void saveLeaderboard();
//
// private:
//     // ---------------------------
//     // Core Management
//     // ---------------------------
//     sf::RenderWindow& window;
//     GameState currentState;
//
//     sf::Font font;
//     sf::Text titleText;
//     sf::Text subtitleText;
//     sf::Text infoText;
//
//     bool showQuitConfirmation = false;
//
//     // ---------------------------
//     // Settings & Leaderboard Data
//     // ---------------------------
//     int lives = 3;
//     int spawnLevel = 1;
//     int selectedPlayerIcon = 0;
//
//     struct LeaderboardEntry {
//         std::string name;
//         int score;
//     };
//     std::vector<LeaderboardEntry> leaderboard;
//
//     // ---------------------------
//     // Buttons & UI Containers
//     // ---------------------------
//     // For each GameState, store a list of unique_ptr<Button>
//     std::unordered_map<GameState, std::vector<std::unique_ptr<Button>>> buttonsByState;
//
//     // Background and overlays
//     sf::RectangleShape background;
//     sf::RectangleShape dialogOverlay;
//
//     // ---------------------------
//     // Creation & Cleanup Helpers
//     // ---------------------------
//     void createMainMenu();
//     void createPauseMenu();
//     void createSettingsMenu();
//     void createGameOverMenu();
//     void createLeaderboardMenu();
//     void createQuitConfirmMenu();
//
//     void loadResources();
//     void resetButtonHighlights();
//
//     // ---------------------------
//     // Rendering Methods
//     // ---------------------------
//     void renderMainMenu();
//     void renderPauseMenu();
//     void renderSettings();
//     void renderLeaderboard();
//     void renderGameOver();
//     void renderQuitConfirmation();
//
//     // ---------------------------
//     // Utility
//     // ---------------------------
//     void processButtons(sf::Event& event);
// };
//
// #endif // SCREEN_MANAGER_H



#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include <SFML/Graphics.hpp>
#include "button.h"
#include "Game_State.h"
#include <vector>
#include <string>

class ScreenManager {
private:
    sf::RenderWindow& window;
    GameState currentState;

    // UI Elements
    sf::Font font;
    sf::Text titleText;
    sf::Text subtitleText;
    sf::Text infoText;

    // Buttons for each screen
    // Main Menu
    Button* startButton;
    Button* leaderboardButton;
    Button* settingsButton;
    Button* quitButton;

    // Pause Menu (in gameplay)
    Button* resumeButton;
    Button* mainMenuButton;
    Button* quitFromPauseButton;

    // Settings
    Button* backButton;
    Button* livesUpButton;
    Button* livesDownButton;
    Button* levelUpButton;
    Button* levelDownButton;
    std::vector<Button*> playerIconButtons;

    // Game Over
    Button* playAgainButton;
    Button* mainMenuFromGameOverButton;

    // Quit Confirmation Dialog
    Button* confirmYesButton;
    Button* confirmNoButton;
    bool showQuitConfirmation;

    // Settings values
    int lives;
    int spawnLevel;
    int selectedPlayerIcon;

    // Leaderboard data
    struct LeaderboardEntry {
        std::string name;
        int score;
    };
    std::vector<LeaderboardEntry> leaderboard;

    // Background elements
    sf::RectangleShape background;
    sf::RectangleShape dialogOverlay;

public:
    // Constructor
    ScreenManager(sf::RenderWindow& win);
    ~ScreenManager();

    // Initialize all UI elements
    void initialize();

    // Update based on current state
    void update(sf::Event& event);

    // Render based on current state
    void render();

    // State management
    void setState(GameState newState);
    GameState getState() const;

    // Settings getters
    int getLives() const { return lives; }
    int getSpawnLevel() const { return spawnLevel; }
    int getSelectedPlayerIcon() const { return selectedPlayerIcon; }

    // Leaderboard management
    void addScore(const std::string& name, int score);
    void loadLeaderboard();
    void saveLeaderboard();

private:
    // Screen rendering methods
    void renderMainMenu();
    void renderPauseMenu();
    void renderSettings();
    void renderLeaderboard();
    void renderGameOver(int finalScore);
    void renderQuitConfirmation();

    // Button creation helpers
    void createMainMenuButtons();
    void createPauseMenuButtons();
    void createSettingsButtons();
    void createGameOverButtons();
    void createQuitConfirmButtons();

    // Cleanup methods
    void deleteMainMenuButtons();
    void deletePauseMenuButtons();
    void deleteSettingsButtons();
    void deleteGameOverButtons();
    void deleteQuitConfirmButtons();
    void deleteAllButtons();

    // Load resources
    void loadResources();
};

#endif