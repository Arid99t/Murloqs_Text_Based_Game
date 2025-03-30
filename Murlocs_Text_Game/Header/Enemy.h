// enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include "Header/Character.h"
#include <string>
#include <vector>
using namespace std;

// Enemy class derived from Character
class Enemy : public Character {
protected:
    int experienceReward;

public:
    // Constructor
    Enemy(const string& name, int health, int meleeAtk, int rangedAtk, int def, int expReward);

    // Virtual destructor
    virtual ~Enemy() = default;

    // Override virtual methods from Character
    void attack(Character& target) override;
    void takeDamage(int damage) override;
    void heal(int amount) override;
    void displayStats() const override;

    // Enemy-specific methods
    virtual int getExperienceReward() const;

    // Static method to generate enemy names
    static string generateEnemyName();
};

// Boss class derived from Enemy
class Boss : public Enemy {
private:
    vector<string> specialAttacks;
    int specialAttackDamage;

public:
    // Constructor
    Boss(const string& name, int health, int meleeAtk, int rangedAtk, int def, int expReward);

    // Override attack method to include special attacks
    void attack(Character& target) override;

    // Override takeDamage to potentially heal
    void takeDamage(int damage) override;

    // Boss-specific methods
    void addSpecialAttack(const string& attackName);
    void useSpecialAttack(Character& target, int attackIndex);
    int getSpecialAttackCount() const;

    // Method overloading for demonstration
    void displayStats() const override;
    void displayStats(bool showSpecialAttacks) const;
};
#endif