// level.h
#ifndef LEVEL_H
#define LEVEL_H

#include "Header/Player.h"
#include "Header/Enemy.h"
#include <vector>
#include <memory>
using namespace std;

class Level {
private:
    int levelNumber;
    string levelName;
    string description;
    vector<unique_ptr<Enemy>> enemies;
    unique_ptr<Item> reward;
    unique_ptr<Ability> newAbility;

public:
    // Constructor
    Level(int number, const string& name, const string& desc);

    // Virtual destructor
    virtual ~Level() = default;

    // Getters
    int getLevelNumber() const;
    string getLevelName() const;
    string getDescription() const;
    int getEnemyCount() const;

    // Methods to add enemies, rewards, and abilities
    void addEnemy(unique_ptr<Enemy> enemy);
    void setReward(unique_ptr<Item> item);
    void setNewAbility(unique_ptr<Ability> ability);

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