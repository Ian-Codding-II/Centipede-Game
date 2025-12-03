/**
 * @file ScreenManager.cpp
 * @author Ian Codding II
 * @brief Implementation of ScreenManager - coordinates all screens
 * @version 2.0
 * @date 2025-10-27
 *
 * @copyright Copyright (c) 2025
 */

#include "../includes/ScreenManager.h"
#include "../includes/errorHandler.h"
#include "../includes/GameOverScreen.h"
#include "../includes/LeaderboardScreen.h"
#include "../includes/MainMenuScreen.h"
#include "../includes/PauseScreen.h"
#include "../includes/SettingsScreen.h"
#include <iostream>

/**
 * @brief Constructor - initialize ScreenManager
 *
 * Takes a reference to the main window so all screens can draw to it.
 * Sets initial state to MENU (start with main menu).
 * Sets currentScreen to nullptr (will be created in initialize()).
 *
 * We store a REFERENCE to the window (not a copy) because:
 * - We want all screens to share THE SAME window object
 * - Creating new windows is expensive and unnecessary
 * - References save memory compared to copying
 *
 * @param win Reference to the main SFML window created in main()
 */
ScreenManager::ScreenManager(sf::RenderWindow &win)
    : window(win)
    , currentState(GameState::MENU)
    , currentScreen(nullptr) {

    // Log that we're creating the ScreenManager
    std::cout << "[ScreenManager] Constructor called" << std::endl;
}

/**
 * @brief Destructor - clean up all screens
 *
 * When the program ends, this destructor is automatically called.
 * It iterates through ALL screens we've created and deletes them.
 * This prevents memory leaks.
 *
 * The screens map contains all Screen pointers we've created.
 * We loop through each one and delete it to free the memory.
 *
 * This is important because each Screen allocates memory for buttons
 * and other UI elements. If we don't delete them, that memory stays
 * allocated until the program ends (memory leak).
 */
ScreenManager::~ScreenManager() {
    std::cout << "[ScreenManager] Destructor called - cleaning up screens" << std::endl;

    // Iterate through all screens in the map
    // It's a map<GameState, Screen*>, so we iterate through key-value pairs
    for (auto &pair : screens) {
        // pair.first = GameState (the key)
        // pair.second = Screen* (the pointer to delete)

        if (pair.second != nullptr) {
            // Call cleanup() to let the screen delete its own buttons
            pair.second->cleanup();

            // Delete the screen object itself
            delete pair.second;
            pair.second = nullptr;

            std::cout << "[ScreenManager] Deleted screen for state: "
                      << static_cast<int>(pair.first) << std::endl;
        }
    }

    // Clear the map (remove all entries)
    screens.clear();

    std::cout << "[ScreenManager] All screens cleaned up" << std::endl;
}

/**
 * @brief Initialize - load font and create the first screen
 *
 * This must be called after the constructor, once the window is ready.
 * It does two things:
 * 1. Loads the font from the assets folder
 * 2. Creates the initial screen (main menu)
 *
 * We separate this from the constructor because creating SFML objects
 * needs the OpenGL context to be initialized, which happens when the
 * window is created in main.cpp.
 *
 * Throws ResourceError if font fails to load.
 */
void ScreenManager::initialize() {
    std::cout << "[ScreenManager] Initializing..." << std::endl;

    // Try to load the font
    // The font file should be in assets/fonts/
    if (!font.loadFromFile("assets/fonts/Balins_Font.ttf")) {
        // If font loading fails, throw an error
        logError("ScreenManager", "Failed to load font: assets/fonts/Balins_Font.ttf");
        throw ResourceError("Font loading failed");
    }

    std::cout << "[ScreenManager] Font loaded successfully" << std::endl;

    // Create the initial screen (main menu)
    setState(GameState::MENU);

    std::cout << "[ScreenManager] Initialization complete" << std::endl;
}

/**
 * @brief Update - forward events to current screen and handle state transitions
 *
 * Called every frame for each event (mouse click, key press, window close, etc.)
 *
 * What happens:
 * 1. The current screen's update() method is called with the event
 * 2. The screen processes the event and returns a GameState
 * 3. If the returned state is different from current state, we transition
 * 4. If same state, we stay on the current screen
 *
 * Example flow:
 * - Player is on MainMenu (currentState = MENU)
 * - Player clicks "Start Game" button
 * - MainMenuScreen::update() returns PLAYING state
 * - We detect state changed from MENU to PLAYING
 * - setState(PLAYING) is called
 * - New PlayingScreen is created and initialized
 * - Next frame, updates go to PlayingScreen instead of MainMenuScreen
 *
 * @param event The SFML event to process
 */
void ScreenManager::update(sf::Event &event) {
    // Make sure we have a current screen
    if (currentScreen == nullptr) {
        logError("ScreenManager", "currentScreen is nullptr in update()");
        return;
    }

    // Call the current screen's update method
    // This processes the event and returns the next state to go to
    GameState nextState = currentScreen->update(event);

    // Check if the state changed
    if (nextState != currentState) {
        std::cout << "[ScreenManager] State transition detected: "
                  << static_cast<int>(currentState) << " -> "
                  << static_cast<int>(nextState) << std::endl;

        // Transition to the new state
        setState(nextState);
    }
}

/**
 * @brief Render - draw the current screen
 *
 * Called every frame to draw all UI elements.
 * Simply forwards the call to the current screen's render() method.
 * Each screen knows how to draw itself.
 */
void ScreenManager::render() {
    // Make sure we have a current screen
    if (currentScreen == nullptr) {
        logError("ScreenManager", "currentScreen is nullptr in render()");
        return;
    }

    // Forward the render call to the current screen
    currentScreen->render();
}

/**
 * @brief Change to a different state/screen
 *
 * This is the core state transition logic. When we need to switch screens:
 * 1. Cleanup the current screen
 * 2. Update currentState
 * 3. Get or create the new screen
 * 4. Initialize the new screen
 *
 * This ensures proper cleanup of old screens and setup of new ones.
 *
 * @param newState The state to transition to
 */
void ScreenManager::setState(GameState newState) {
    std::cout << "[ScreenManager] setState() called: transitioning to state "
              << static_cast<int>(newState) << std::endl;

    // ===== SPECIAL CASE: PLAYING STATE =====
    // PLAYING is handled by the Game class, not by ScreenManager
    // So we just update the state and leave currentScreen as is
    if (newState == GameState::PLAYING) {
        currentState = newState;
        std::cout << "[ScreenManager] Transitioning to PLAYING - Game class takes over" << std::endl;
        return; // Don't proceed with normal screen setup
    }

    // ===== NORMAL CASE: UI STATES (MENU, SETTINGS, PAUSED, etc.) =====

    // If we have a current screen, clean it up
    // We DON'T delete it - just call cleanup() to delete its buttons
    // This allows us to reuse the screen if we return to this state
    if (currentScreen != nullptr) {
        currentScreen->cleanup();
    }

    // Update the current state variable
    currentState = newState;

    // Get the screen for this state (creates if needed, or returns existing)
    currentScreen = getScreen(newState);

    // If screen is valid, initialize it
    if (currentScreen != nullptr) {
        currentScreen->initialize();
        std::cout << "[ScreenManager] New screen initialized" << std::endl;
    } else {
        logError("ScreenManager", "Failed to get screen for state");
    }
}

/**
 * @brief Get or create a screen for the given state
 *
 * This implements "lazy initialization" - screens are only created when needed.
 *
 * How it works:
 * 1. Check if we already have a screen for this state in the map
 * 2. If yes: return the existing screen (reuse it)
 * 3. If no: create a new screen, store it in the map, return it
 *
 * Benefits of lazy initialization:
 * - Don't waste memory creating screens that might never be used
 * - Game starts faster (only create what's needed)
 * - Reuse screens when returning to previous states
 *
 * Example:
 * - Game starts: only MainMenuScreen is created
 * - Player clicks Start: GameScreen is created when first needed
 * - Player returns to menu: MainMenuScreen is reused (not recreated)
 *
 * @param state The state to get a screen for
 * @return Pointer to the screen, or nullptr if state not implemented
 */
Screen *ScreenManager::getScreen(GameState state) {
    // Check if we've already created a screen for this state
    // screens.find(state) returns an iterator
    // If it's not screens.end(), we found it in the map
    if (screens.find(state) != screens.end()) {
        std::cout << "[ScreenManager] Reusing existing screen for state "
                  << static_cast<int>(state) << std::endl;

        // Return the existing screen
        return screens[state];
    }

    // Screen doesn't exist yet, so create it
    std::cout << "[ScreenManager] Creating new screen for state "
              << static_cast<int>(state) << std::endl;

    Screen *newScreen = nullptr;

    // Create the appropriate screen based on the state
    // Each case creates a new screen of the correct type
    switch (state) {
    case GameState::MENU:
        // Create a MainMenuScreen
        newScreen = new MainMenuScreen(window, font);
        break;

    case GameState::SETTINGS:
        // Create a SettingsScreen
        newScreen = new SettingsScreen(window, font);
        break;

    case GameState::PAUSED:
        // Create a PauseScreen
        newScreen = new PauseScreen(window, font);
        break;

    case GameState::GAME_OVER:
        // Create a GameOverScreen
        newScreen = new GameOverScreen(window, font, *this);
        break;

    case GameState::LEADERBOARD:
        // Create a LeaderboardScreen
        newScreen = new LeaderboardScreen(window, font);
        break;

    case GameState::PLAYING:
        // PlayingScreen is not created here
        // Gameplay is handled differently in main.cpp
        // We return nullptr to indicate this isn't a UI screen
        std::cout << "[ScreenManager] PLAYING state doesn't use ScreenManager" << std::endl;
        return nullptr;

    default:
        // Unknown state
        logError("ScreenManager", "Unknown state in getScreen()");
        return nullptr;
    }

    // Store the new screen in the map for future use
    if (newScreen != nullptr) {
        screens[state] = newScreen;
        std::cout << "[ScreenManager] Screen created and stored for state "
                  << static_cast<int>(state) << std::endl;
    }

    return newScreen;
}