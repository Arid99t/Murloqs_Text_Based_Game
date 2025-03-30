// level.cpp
#include "Header/Level.h"
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>
using namespace std;

// Constructor implementation
Level::Level(int number, const string& name, const string& desc)
    : levelNumber(number), levelName(name), description(desc) {
}

// Getters implementation
int Level::getLevelNumber() const {
    return levelNumber;
}

string Level::getLevelName() const {
    return levelName;
}

string Level::getDescription() const {
    return description;
}

int Level::getEnemyCount() const {
    return enemies.size();
}

// Methods to add enemies, rewards, and abilities
void Level::addEnemy(unique_ptr<Enemy> enemy) {
    enemies.push_back(move(enemy));
}

void Level::setReward(unique_ptr<Item> item) {
    reward = move(item);
}

void Level::setNewAbility(unique_ptr<Ability> ability) {
    newAbility = move(ability);
}

// Methods to display level info
void Level::displayLevelInfo() const {
    cout << "\n========== LEVEL " << levelNumber << ": " << levelName << " ==========" << endl;
    cout << description << endl;
    cout << "Number of enemies: " << enemies.size() << endl;
    cout << "=================================================" << endl;
}

// Method to run the level
bool Level::runLevel(Player& player) {
    // Display level info
    displayLevelInfo();

    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Combat with each enemy
    for (auto& enemy : enemies) {
        if (!combat(player, *enemy)) {
            // Player was defeated
            return false;
        }

        // Short rest between enemies
        cout << "\nYou take a short rest before facing the next enemy..." << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    // Level completed
    cout << "\n?? LEVEL " << levelNumber << " COMPLETED! ??" << endl;

    // Award rewards
    awardRewards(player);

    // Level up the player
    player.levelUp();

    return true;
}

// Method for combat between player and enemy
bool Level::combat(Player& player, Enemy& enemy) {
    cout << "\n?? COMBAT START: " << player.getName() << " vs " << enemy.getName() << " ??" << endl;

    // Display stats before combat
    player.displayStats();
    enemy.displayStats();

    cout << "\nPress Enter to begin combat...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Combat loop
    while (player.checkIsAlive() && enemy.checkIsAlive()) {
        // Player's turn
        playerTurn(player, enemy);

        // Check if enemy is defeated
        if (!enemy.checkIsAlive()) {
            cout << "\n" << enemy.getName() << " has been defeated!" << endl;
            break;
        }

        // Short pause between turns
        this_thread::sleep_for(chrono::milliseconds(500));

        // Enemy's turn
        enemyTurn(player, enemy);

        // Check if player is defeated
        if (!player.checkIsAlive()) {
            cout << "\nYou have been defeated by " << enemy.getName() << "!" << endl;
            return false;
        }

        // Display current health
        cout << "\nHealth: " << player.getName() << ": " << player.getCurrentHealth()
            << "/" << player.getMaxHealth() << " | "
            << enemy.getName() << ": " << enemy.getCurrentHealth()
            << "/" << enemy.getMaxHealth() << endl;

        // Short pause between rounds
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    cout << "\n?? COMBAT END ??" << endl;

    return player.checkIsAlive();
}

// Method to handle player's turn in combat
void Level::playerTurn(Player& player, Enemy& enemy) {
    cout << "\n==== " << player.getName() << "'s Turn ====" << endl;

    // Show options
    cout << "1. Attack" << endl;
    cout << "2. Heal" << endl;
    cout << "3. Display Stats" << endl;

    // Get player choice
    int choice;
    cout << "\nEnter your choice (1-3): ";
    while (!(cin >> choice) || choice < 1 || choice > 3) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number between 1 and 3: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
    cout << "\n==== " << enemy.getName() << "'s Turn ====" << endl;

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
        player.addItem(move(reward));
    }

    // Award ability if available
    if (newAbility) {
        player.addAbility(move(newAbility));
    }
}