
// ============================================================================
// LEADERBOARD MANAGEMENT
// These handle saving/loading high scores to/from a file
// ============================================================================

#include "../../includes/screenManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>

/**
 * @brief Add a new score to the leaderboard
 * 
 * Adds the score, sorts by score (highest first), keeps only top 10, then saves to file.
 * 
 * @param name Player's name
 * @param score Player's score
 */
void ScreenManager::addScore(const std::string& name, int score) {
    std::cout << "[DEBUG] Adding score: " << name << " - " << score << std::endl;
    
    // Create new leaderboard entry
    LeaderboardEntry entry;
    entry.name = name;
    entry.score = score;
    
    // Add to leaderboard vector
    leaderboard.push_back(entry);
    
    // Sort by score in descending order (highest first)
    // Uses a lambda function to compare two entries
    std::sort(leaderboard.begin(), leaderboard.end(),
        [](const LeaderboardEntry& a, const LeaderboardEntry& b) {
            return a.score > b.score;  // Return true if a should come before b
        });
    
    // Keep only top 10 scores
    if (leaderboard.size() > 10) {
        leaderboard.resize(10);  // Removes entries beyond index 9
    }
    
    // Save updated leaderboard to file
    saveLeaderboard();
    
    std::cout << "[DEBUG] Score added and leaderboard saved" << std::endl;
}

/**
 * @brief Load leaderboard from file
 * 
 * Reads "leaderboard.txt" and populates the leaderboard vector.
 * File format: each line has "name score" (space separated)
 * If file doesn't exist, leaderboard starts empty.
 */
void ScreenManager::loadLeaderboard() {
    std::cout << "[DEBUG] Loading leaderboard from file..." << std::endl;
    
    // Open file for reading
    std::ifstream file("leaderboard.txt");
    
    if (file.is_open()) {
        // Clear existing leaderboard
        leaderboard.clear();
        
        // Read entries line by line
        // Format: "PlayerName 12345"
        std::string name;
        int score;
        while (file >> name >> score) {
            LeaderboardEntry entry;
            entry.name = name;
            entry.score = score;
            leaderboard.push_back(entry);
        }
        
        file.close();
        std::cout << "[DEBUG] Loaded " << leaderboard.size() << " leaderboard entries" << std::endl;
    } else {
        std::cout << "[DEBUG] No leaderboard file found, starting empty" << std::endl;
    }
}

/**
 * @brief Save leaderboard to file
 * 
 * Writes the leaderboard vector to "leaderboard.txt".
 * Each entry is written as "name score" on its own line.
 */
void ScreenManager::saveLeaderboard() {
    std::cout << "[DEBUG] Saving leaderboard to file..." << std::endl;
    
    // Open file for writing (overwrites if exists)
    std::ofstream file("leaderboard.txt");
    
    if (file.is_open()) {
        // Write each entry
        // Format: "PlayerName 12345\n"
        for (size_t i = 0; i < leaderboard.size(); i++) {
            file << leaderboard[i].name << " " << leaderboard[i].score << "\n";
        }
        
        file.close();
        std::cout << "[DEBUG] Leaderboard saved successfully" << std::endl;
    } else {
        std::cerr << "[ERROR] Could not save leaderboard to file" << std::endl;
    }
}