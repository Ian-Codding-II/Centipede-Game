/**
 * @file game.cpp
 * @author Ian Codding II
 * @brief Main game controller - orchestrates all gameplay
 * @version 3.2 - Complete integration
 * @date 2025-12-03
 * @copyright Copyright (c) 2025
 */

#include "../includes/game.h"
#include "../includes/errorHandler.h"
#include <cstdlib>
#include <iostream>

/**
 * @brief Constructor - initialize game systems
 * Setup window reference, screen manager, and UI text.
 * @param win Reference to render window
 * @param screenMngr Reference to ScreenManager
 */
Game::Game(sf::RenderWindow &win, ScreenManager &screenMngr)
    : window(win),
      screenManager(screenMngr),
      currentState(GameState::PLAYING),
      isGameOver(false),
      isPaused(false),
      score(0),
      lives(3),
      level(1),
      player(nullptr),
      centipede(nullptr),
      grid(nullptr) {
    std::cout << "[Game] Constructor called" << std::endl;

    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color::Black);

    sf::Font &font = screenManager.getFont();

    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::Green);
    scoreText.setPosition(10, 10);

    livesText.setFont(font);
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::Green);
    livesText.setPosition(window.getSize().x - 200, 10);

    levelText.setFont(font);
    levelText.setCharacterSize(20);
    levelText.setFillColor(sf::Color::Green);
    levelText.setPosition(window.getSize().x / 2 - 50, 10);

    if (!loadTextures()) {
        logError("Game", "Failed to load atlas texture");
    }

    std::cout << "[Game] Constructor completed" << std::endl;
}

/**
 * @brief Destructor - cleanup all resources
 * Calls cleanup() to free memory for all game objects.
 */
Game::~Game() {
    std::cout << "[Game] Destructor called" << std::endl;
    cleanup();
}
/**
 * @brief Initialize - setup new game session
 * Creates grid, player, centipede, and mushrooms.
 * Gets settings from SettingsScreen.
 */
void Game::initialize() {
    std::cout << "[Game] initialize() called" << std::endl;

    if (grid == nullptr) {
        grid = new Grid(sf::FloatRect(125, 80, 950, 720), 16);
        std::cout << "[Game] Grid created: 950x720 at (125,80)" << std::endl;
    }

    SettingsScreen *settings =
        (SettingsScreen *)screenManager.getScreen(GameState::SETTINGS);

    if (settings != nullptr) {
        lives = settings->getLives();
        level = settings->getSpawnLevel();
        std::cout << "[Game] Settings: Lives=" << lives << ", Level=" << level << std::endl;
    }

    score = 0;
    isGameOver = false;
    isPaused = false;
    currentState = GameState::PLAYING;

    player = new sf::RectangleShape();
    Player::startPlayer(*player, texture);

    centipede = new Centipede(texture, 5, sf::Vector2f(200, 100), sf::Vector2i(2, 2));
    //std::cout << "[Game] Centipede created" << std::endl;

    generateMushrooms();

    std::cout << "[Game] Game ready to play" << std::endl;
}

/**
 * @brief Handle input events during gameplay
 * Processes pause/resume (P or ESC key).
 * @param event SFML event to process
 */
void Game::handleInput(const sf::Event &event) {
    if (isGameOver)
        return;

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::P || 
            event.key.code == sf::Keyboard::Escape) {
            isPaused = !isPaused;
            currentState = isPaused ? GameState::PAUSED : GameState::PLAYING;
            std::cout << "[Game] " << (isPaused ? "PAUSED" : "RESUMED") << std::endl;
        }
    }
}

/**
 * @brief Update - game logic each frame
 * Updates player, bullets, mushrooms, centipede.
 * Handles collisions between all objects.
 * @param dt Delta time since last frame
 */
void Game::update(float dt) {
    if (isPaused || isGameOver)
        return;

    // Update player movement
    if (player) {
        Player::movePlayer(*player, dt, grid->GetRegion());
    }

    // Update bullets
    Bullet::shoot(player->getPosition(), dt, texture);
    
    for (int i = (int)Bullet::bullets.size() - 1; i >= 0; i--) {
        Bullet::bullets[i]->update(dt);
        
        if (!Bullet::bullets[i]->isAlive()) {
            delete Bullet::bullets[i];
            Bullet::bullets.erase(Bullet::bullets.begin() + i);
        }
    }
    //std::cout << " NOW!!!!" << '\n';
for (int i = (int)Bullet::bullets.size() - 1; i >= 0; i--) {
        Bullet* bullet = Bullet::bullets[i];
        bullet->update(dt);
        if (!(bullet->isAlive())) {
        sf::Vector2f pos = bullet->getPosition();       // position as float
        sf::Vector2i intPos(static_cast<int>(pos.x), static_cast<int>(pos.y)); // convert to int
            std::cout << "The x value for the bullet = " << intPos.x
                << " and the y value for the bullet = " << intPos.y << '\n';
        delete bullet;
        Bullet::bullets.erase(Bullet::bullets.begin() + i);
        std::cout << "[Game] Bullet removed (off-screen)" << std::endl;
                        }
    }
    

    
    // Update mushrooms
    for (auto mushroom : mushrooms) {
        if (mushroom) {
            mushroom->update();
        }
    }

    // Remove destroyed mushrooms
    for (int i = (int)mushrooms.size() - 1; i >= 0; i--) {
        if (mushrooms[i]->isDestroyed()) {
            delete mushrooms[i];
            mushrooms.erase(mushrooms.begin() + i);
        }
    }

    // Update centipede
    
    if (centipede) {
        centipede->move(dt, *grid);
        centipede->update(dt);
    }

    // Handle collisions
    handleCollisions();

    updateUI();
    checkGameOver();

    static int frameCount = 0;
    if (++frameCount % 60 == 0) {
        debugPrint();
    }
}

/**
 * @brief Handle all collision detection
 * Checks bullet-mushroom, bullet-centipede, and player-centipede.
 */
void Game::handleCollisions() {
    // Bullet vs Mushroom
    for (int b = (int)Bullet::bullets.size() - 1; b >= 0; b--) {
        if (!Bullet::bullets[b]->isAlive()) continue;
        
        sf::FloatRect bulletBounds = Bullet::bullets[b]->getSprite().getGlobalBounds();
        
        for (int m = (int)mushrooms.size() - 1; m >= 0; m--) {
            sf::Vector2f mushPos = mushrooms[m]->getPosition();
            sf::FloatRect mushBounds(mushPos.x - 16, mushPos.y - 16, 32, 32);
            
            if (bulletBounds.intersects(mushBounds)) {
                mushrooms[m]->hit(1);
                Bullet::bullets[b]->kill();
                score += 5;
                std::cout << "[Game] Bullet hit mushroom! Score: " << score << std::endl;
                break;
            }
        }
    }

    // Bullet vs Centipede
    if (centipede) {
        for (int b = (int)Bullet::bullets.size() - 1; b >= 0; b--) {
            if (!Bullet::bullets[b]->isAlive()) continue;
            
            sf::FloatRect bulletBounds = Bullet::bullets[b]->getSprite().getGlobalBounds();
            sf::Vector2f centipedePos = centipede->getPosition();
            sf::FloatRect centipedeBounds(centipedePos.x , centipedePos.y , 32, 32);
            
            if (bulletBounds.intersects(centipedeBounds)) {
                Bullet::bullets[b]->kill();
                score += 100;
                std::cout << "[Game] Bullet hit centipede! Score: " << score << std::endl;
                Bullet::bullets[b]->kill();
                centipede->hit();
            }
        }
    }

    // Player vs Centipede
    if (centipede && player) {
        sf::FloatRect playerBounds = player->getGlobalBounds();
        sf::Vector2f centipedePos = centipede->getPosition();
        sf::FloatRect centipedeBounds(centipedePos.x - 16, centipedePos.y - 16, 32, 32);
        
        if (playerBounds.intersects(centipedeBounds)) {
            lives--;
            std::cout << "[Game] Player hit by centipede! Lives: " << lives << std::endl;
        }
    }
}

/**
 * @brief Render - draw all game objects to window
 * Order: background, mushrooms, centipede, bullets, player, UI.
 */
void Game::render() {
    window.draw(background);

    for (auto mushroom : mushrooms) {
        if (mushroom) window.draw(*mushroom);
    }

    for (Bullet* bullet : Bullet::bullets)
    {
        if (bullet )
        {
            window.draw(bullet->getSprite());
        }
    }

    if (centipede) {
        window.draw(*centipede);
    }

    for (auto bullet : Bullet::bullets) {
        window.draw(bullet->getSprite());
    }

    if (player) {
        window.draw(*player);
    }

    window.draw(scoreText);
    window.draw(livesText);
    window.draw(levelText);
}

/**
 * @brief Get current game state
 * @return GameState enum (PLAYING, PAUSED, GAME_OVER, etc)
 */
GameState Game::getState() const {
    return currentState;
}

/**
 * @brief Set game state with debug logging
 * @param newState New state to transition to
 */
void Game::setState(GameState newState) {
    if (newState != currentState) {
        currentState = newState;
        std::cout << "[Game] State: " << static_cast<int>(newState) << std::endl;
    }
}

/**
 * @brief Set pause state
 * @param paused true to pause, false to resume
 */
void Game::setPaused(bool paused) {
    isPaused = paused;
    currentState = paused ? GameState::PAUSED : GameState::PLAYING;
    std::cout << "[Game] Game " << (paused ? "paused" : "resumed") << std::endl;
}

/**
 * @brief Get current pause state
 * @return true if paused, false if playing
 */
bool Game::getPaused() const {
    return isPaused;
}

/**
 * @brief Cleanup - free all allocated resources
 * Deletes player, centipede, mushrooms, bullets, grid.
 */
void Game::cleanup() {
    std::cout << "[Game] cleanup() called" << std::endl;

    if (player != nullptr) {
        delete player;
        player = nullptr;
    }

    if (centipede != nullptr) {
        delete centipede;
        centipede = nullptr;
    }

    for (auto mushroom : mushrooms) {
        if (mushroom != nullptr) delete mushroom;
    }
    mushrooms.clear();

    for (auto bullet : Bullet::bullets) {
        if (bullet != nullptr) {
            delete bullet;
        }
    }
    Bullet::bullets.clear();

    if (grid != nullptr) {
        delete grid;
        grid = nullptr;
    }

    std::cout << "[Game] Cleanup completed" << std::endl;
}

/**
 * @brief Load game textures from atlas file
 * @return true if successful, false on error
 */
bool Game::loadTextures() {
    if (!texture.loadFromFile("assets/sprites/atlas.png")) {
        logError("Game", "Failed to load atlas texture");
        return false;
    }

    std::cout << "[Game] Atlas loaded" << std::endl;
    return true;
}

/**
 * @brief Generate random mushroom obstacles
 * Spawns at random positions within grid bounds.
 * Count = 10 + (level * 2). Scaled 3x3.
 */
void Game::generateMushrooms() {
    if (grid == nullptr) {
        std::cerr << "[Game] ERROR: Grid not initialized!" << std::endl;
        return;
    }
    int mushroomCount = 10 + (level * 2);
    std::cout << "[Game] Generating " << mushroomCount << " mushrooms" << std::endl;

    for (int i = 0; i < mushroomCount; i++) {
        float randomX = rand() % (int)grid->GetRegion().width + grid->GetRegion().left;
        float randomY = rand() % (int)(grid->GetRegion().height - 250) + grid->GetRegion().top + 50;

        Mushroom *mushroom = new Mushroom(
            texture,
            sf::IntRect(64, 64, 32, 32),
            sf::Vector2f(randomX, randomY),
            4,
            false);

        mushroom->setScale(sf::Vector2i(3, 3));
        mushrooms.push_back(mushroom);
    }
}

/**
 * @brief Check game over condition
 * If lives <= 0: set game over, save top 10 scores.
 */
void Game::checkGameOver() {
    if (lives <= 0) {
        isGameOver = true;
        currentState = GameState::GAME_OVER;

        std::cout << "[Game] GAME OVER - Score: " << score << std::endl;

        GameOverScreen *gameOverScreen =
            (GameOverScreen *)screenManager.getScreen(GameState::GAME_OVER);

        if (gameOverScreen != nullptr) {
            gameOverScreen->initialize();
            gameOverScreen->setScore(score);

            LeaderboardScreen *leaderboard =
                (LeaderboardScreen *)screenManager.getScreen(GameState::LEADERBOARD);

            if (leaderboard != nullptr) {
                leaderboard->initialize();
                if (leaderboard->isTopScore(score)) {
                    std::cout << "[Game] Top 10 score! Prompt for name" << std::endl;
                    gameOverScreen->setIsTopScore(true);
                }
            }
        }

        
    }
}

/**
 * @brief Save player score to leaderboard
 * Called after player submits name on game over screen.
 * @param playerName Name entered by player
 */
void Game::savePlayerScore(const std::string &playerName) {
    LeaderboardScreen *leaderboard =
        (LeaderboardScreen *)screenManager.getScreen(GameState::LEADERBOARD);

    if (leaderboard != nullptr) {
        leaderboard->initialize();
        leaderboard->addScore(playerName, score);
        leaderboard->saveToFile();
        std::cout << "[Game] Score saved: " << playerName << " - " << score << std::endl;
    }
}

/**
 * @brief Update UI text elements
 * Updates score, lives, and level display.
 */
void Game::updateUI() {
    scoreText.setString("Score: " + std::to_string(score));
    livesText.setString("Lives: " + std::to_string(lives));
    levelText.setString("Level: " + std::to_string(level));
}

/**
 * @brief Debug print game state
 * Logs score, lives, level, and object counts.
 */
void Game::debugPrint() const {
    std::cout << "[Game] Score: " << score << " | Lives: " << lives
              << " | Level: " << level << " | Bullets: " << Bullet::bullets.size()
              << " | Mushrooms: " << mushrooms.size() << std::endl;
}
