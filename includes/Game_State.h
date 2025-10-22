/**
 * @file Game_State.h
 * @author Ian Codding II
 * @brief 
 * @version 0.1
 * @date 2025-10-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef GAME_STATE_H
#define GAME_STATE_H

// Game_State.h: Defines the game states for state machine management.
// This allows the game to transition between menu, playing, paused, and game over screens.
// Source: Standard game design pattern for finite state machines (FSM) - https://en.wikipedia.org/wiki/Finite-state_machine
// In Centipede, states handle menu selection and game over resets without complex menus.
// Source: Simplified from Atari Centipede's single-player loop with score-based continues - https://en.wikipedia.org/wiki/Centipede_(video_game)

#include <string>

// Enum for game states: MENU for start screen, PLAYING for active gameplay,
// PAUSED for temporary halt (e.g., on escape key), GAME_OVER for end screen.
enum class GameState {
    MENU,      // Initial state: Display title and instructions, wait for start input.
    PLAYING,   // Core loop: Update entities, handle input, check collisions.
    PAUSED,    // Freeze updates, show pause menu; resume on input.
    GAME_OVER  // Display score, high score; option to restart or quit.
};

// Simple struct to hold state-specific data if needed (e.g., menu options).
// Currently unused, but extensible for sub-states like high score entry.
struct StateData {
    std::string message;  // e.g., "Press Enter to Start" for MENU.
    GameState nextState;  // Pending transition target.
};

#endif // GAME_STATE_H