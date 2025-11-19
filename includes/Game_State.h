/**
 * @file Game_State.h
 * @author Ian Codding II
 * @brief Defines all valid game states and utility structures for state management.
 * @version 0.1
 * @date 2025-10-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>

/**
 * @enum GameState
 * @brief Represents all possible top-level states of the game.
 *
 * Each state corresponds to a distinct screen or mode.
 * The ScreenManager uses this enum to determine which logic
 * and UI elements to update/render.
 */
enum class GameState {
    MENU,        // Main menu with start, settings, leaderboard, quit buttons
    PLAYING,     // Active gameplay
    PAUSED,      // Game frozen, pause menu visible
    GAME_OVER,   // End screen with score and restart options
    SETTINGS,    // Settings menu (lives, spawn level, player icon)
    LEADERBOARD  // High score display
};

/**
 * @struct StateData
 * @brief Optional structure for passing contextual data between states.
 *
 * Example: When moving from GAME_OVER → MENU, you might include
 * the player's final score or name here.
 */
struct StateData {
    std::string message;      // e.g., "Press Enter to Start" for MENU
    GameState nextState;      // Pending transition target
    int additionalData;       // Generic data field for state-specific info
    
    StateData() 
        : message(""),
          nextState(GameState::MENU),
          additionalData(0) {}
};

/**
 * @brief Converts a GameState enum to a readable string.
 * @param state The GameState to convert.
 * @return A const char* string (e.g., "MENU", "PLAYING").
 */const char* gameStateToString(GameState state);

#endif // GAME_STATE_H