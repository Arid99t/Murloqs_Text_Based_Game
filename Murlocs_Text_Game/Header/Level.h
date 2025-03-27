// level.h
#ifndef LEVEL_H
#define LEVEL_H

#include "player.h"
#include "enemy.h"
#include <vector>
#include <memory>

class Level {
private:
    int levelNumber;
    std::string levelName;
    std::string description;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::unique_ptr<Item> reward;
    std::unique_ptr<Ability> newAbility;

public:
    // Constructor
    Level(int number, const std::string& name, const std::string& desc);

    // Virtual destructor
    virtual ~Level() = default;

    // Getters
    int getLevelNumber() const;
    std::string getLevelName() const;
    std::string getDescription() const;
    int getEnemyCount() const;

    // Methods to add enemies, rewards, and abilities
    void addEnemy(std::unique_ptr<Enemy> enemy);
    void setReward(std::unique_ptr<Item> item);
    void setNewAbility(std::unique_ptr<Ability> ability);

    // Methods to display level info
    void displayLevelInfo() const;

    // Method to run the level
    bool runLevel(Player& player);

    // Method for combat between player and enemy
    bool combat(Player& player, Enemy& enemy);

    // Method to handle player's turn in combat
    void playerTurn(Player& player, Enemy& enemy);

    // Method to handle enemy's turn in combat
    void enemyTurn(Player& player, Enemy& enemy);

    // Method to award rewards after level completion
    void awardRewards(Player& player);
};

#endif // LEVEL_H