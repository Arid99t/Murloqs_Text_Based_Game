// level.cpp
#include "level.h"
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>

// Constructor implementation
Level::Level(int number, const std::string& name, const std::string& desc)
    : levelNumber(number), levelName(name), description(desc) {
}

// Getters implementation
int Level::getLevelNumber() const {
    return levelNumber;
}

std::string Level::getLevelName() const {
    return levelName;
}

std::string Level::getDescription() const {
    return description;
}

int Level::getEnemyCount() const {
    return enemies.size();
}

// Methods to add enemies, rewards, and abilities
void Level::addEnemy(std::unique_ptr<Enemy> enemy) {
    enemies.push_back(std::move(enemy));
}

void Level::setReward(std::unique_ptr<Item> item) {
    reward = std::move(item);
}

void Level::setNewAbility(std::unique_ptr<Ability> ability) {
    newAbility = std::move(ability);
}

// Methods to display level info
void Level::displayLevelInfo() const {
    std::cout << "\n========== LEVEL " << levelNumber << ": " << levelName << " ==========" << std::endl;
    std::cout << description << std::endl;
    std::cout << "Number of enemies: " << enemies.size() << std::endl;
    std::cout << "=================================================" << std::endl;
}

// Method to run the level
bool Level::runLevel(Player& player) {
    // Display level info
    displayLevelInfo();

    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Combat with each enemy
    for (auto& enemy : enemies) {
        if (!combat(player, *enemy)) {
            // Player was defeated
            return false;
        }

        // Short rest between enemies
        std::cout << "\nYou take a short rest before facing the next enemy..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Level completed
    std::cout << "\n?? LEVEL " << levelNumber << " COMPLETED! ??" << std::endl;

    // Award rewards
    awardRewards(player);

    // Level up the player
    player.levelUp();

    return true;
}

// Method for combat between player and enemy
bool Level::combat(Player& player, Enemy& enemy) {
    std::cout << "\n?? COMBAT START: " << player.getName() << " vs " << enemy.getName() << " ??" << std::endl;

    // Display stats before combat
    player.displayStats();
    enemy.displayStats();

    std::cout << "\nPress Enter to begin combat...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Combat loop
    while (player.checkIsAlive() && enemy.checkIsAlive()) {
        // Player's turn
        playerTurn(player, enemy);

        // Check if enemy is defeated
        if (!enemy.checkIsAlive()) {
            std::cout << "\n" << enemy.getName() << " has been defeated!" << std::endl;
            break;
        }

        // Short pause between turns
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Enemy's turn
        enemyTurn(player, enemy);

        // Check if player is defeated
        if (!player.checkIsAlive()) {
            std::cout << "\nYou have been defeated by " << enemy.getName() << "!" << std::endl;
            return false;
        }

        // Display current health
        std::cout << "\nHealth: " << player.getName() << ": " << player.getCurrentHealth()
            << "/" << player.getMaxHealth() << " | "
            << enemy.getName() << ": " << enemy.getCurrentHealth()
            << "/" << enemy.getMaxHealth() << std::endl;

        // Short pause between rounds
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "\n?? COMBAT END ??" << std::endl;

    return player.checkIsAlive();
}

// Method to handle player's turn in combat
void Level::playerTurn(Player& player, Enemy& enemy) {
    std::cout << "\n==== " << player.getName() << "'s Turn ====" << std::endl;

    // Show options
    std::cout << "1. Attack" << std::endl;
    std::cout << "2. Heal" << std::endl;
    std::cout << "3. Display Stats" << std::endl;

    // Get player choice
    int choice;
    std::cout << "\nEnter your choice (1-3): ";
    while (!(std::cin >> choice) || choice < 1 || choice > 3) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number between 1 and 3: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Handle player choice
    switch (choice) {
    case 1: // Attack
        player.attack(enemy);
        break;
    case 2: // Heal
    {
        int healAmount = player.getMaxHealth() * 0.3; // Heal 30% of max health
        player.heal(healAmount);
    }
    break;
    case 3: // Display Stats
        player.displayStats();
        enemy.displayStats();
        // Player gets another turn after viewing stats
        playerTurn(player, enemy);
        break;
    }
}

// Method to handle enemy's turn in combat
void Level::enemyTurn(Player& player, Enemy& enemy) {
    std::cout << "\n==== " << enemy.getName() << "'s Turn ====" << std::endl;

    // Enemy gets a chance to heal if health is low
    if (enemy.getCurrentHealth() < enemy.getMaxHealth() * 0.3 && Character::getRandomNumber(1, 100) <= 30) {
        int healAmount = enemy.getMaxHealth() * 0.2; // Heal 20% of max health
        enemy.heal(healAmount);
    }
    else {
        // Otherwise, attack
        enemy.attack(player);
    }
}

// Method to award rewards after level completion
void Level::awardRewards(Player& player) {
    // Award item if available
    if (reward) {
        player.addItem(std::move(reward));
    }

    // Award ability if available
    if (newAbility) {
        player.addAbility(std::move(newAbility));
    }
}