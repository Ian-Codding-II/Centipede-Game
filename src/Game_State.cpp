/**
 * @file Game_State.cpp
 * @author Ian Codding II
 * @brief Implementation of GameState utilities.
 * @version 0.1
 * @date 2025-10-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "../includes/Game_State.h"


/**
 * @brief Converts a GameState enum into a human-readable string.
 *
 * This function is mainly used for debugging, logging, or console output.
 * Keeping this centralized ensures consistent string representations across the codebase.
 */
const char* gameStateToString(GameState state) {
    switch (state) {
        case GameState::MENU:        return "MENU";
        case GameState::PLAYING:     return "PLAYING";
        case GameState::PAUSED:      return "PAUSED";
        case GameState::GAME_OVER:   return "GAME_OVER";
        case GameState::SETTINGS:    return "SETTINGS";
        case GameState::LEADERBOARD: return "LEADERBOARD";
        default:                     return "UNKNOWN_STATE";
    }
}