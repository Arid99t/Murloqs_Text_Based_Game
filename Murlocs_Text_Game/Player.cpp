// player.cpp
#include "Header/Player.h"
#include <iostream>
#include <algorithm>
using namespace std;
// Constructor implementation
Player::Player(const string& name)
    : Character(name, 100, 15, 10, 5), level(1), blockNextAttack(false), dodgeNextAttack(false) {
}

// Override methods from Character
void Player::attack(Character& target) {
    if (!isAlive) {
        cout << name << " cannot attack because they are defeated!" << endl;
        return;
    }

    // Try to activate a special ability first
    if (tryActivateAbility(target)) {
        return; // Ability was activated and used
    }

    // Regular attack if no ability was activated
    int damage = meleeDamage;
    cout << name << " attacks " << target.getName() << " for " << damage << " damage!" << endl;
    target.takeDamage(damage);
}

void Player::takeDamage(int damage) {
    if (!isAlive) return;

    // Check if block or dodge is active
    if (blockNextAttack) {
        cout << name << " blocks the attack completely!" << endl;
        blockNextAttack = false; // Reset block status
        return;
    }

    if (dodgeNextAttack) {
        cout << name << " dodges the attack completely!" << endl;
        dodgeNextAttack = false; // Reset dodge status
        return;
    }

    // Calculate actual damage after defense
    int actualDamage = calculateDamage(damage);
    cout << name << " takes " << actualDamage << " damage!" << endl;

    // Update health
    setCurrentHealth(currentHealth - actualDamage);

    // Check if player is defeated
    if (currentHealth <= 0) {
        isAlive = false;
        cout << name << " has been defeated!" << endl;
    }
}

void Player::heal(int amount) {
    if (!isAlive) {
        cout << name << " cannot heal because they are defeated!" << endl;
        return;
    }

    int oldHealth = currentHealth;
    setCurrentHealth(currentHealth + amount);
    int actualHeal = currentHealth - oldHealth;

    cout << name << " heals for " << actualHeal << " health points!" << endl;
    cout << "Health: " << currentHealth << "/" << maxHealth << endl;
}

void Player::displayStats() const {
    cout << "\n===== " << name << "'s Stats (Level " << level << ") =====" << endl;
    cout << "Health: " << currentHealth << "/" << maxHealth << endl;
    cout << "Melee Damage: " << meleeDamage << endl;
    cout << "Ranged Damage: " << rangedDamage << endl;
    cout << "Defence: " << defence << endl;

    // Display abilities if any
    if (!abilities.empty()) {
        cout << "\nSpecial Abilities:" << endl;
        for (size_t i = 0; i < abilities.size(); ++i) {
            cout << "  " << (i + 1) << ". " << abilities[i]->getName()
                << " - " << abilities[i]->getDescription()
                << " (" << abilities[i]->getActivationChance() << "% chance)" << endl;
        }
    }

    // Display inventory if any
    if (!inventory.empty()) {
        cout << "\nInventory:" << endl;
        for (size_t i = 0; i < inventory.size(); ++i) {
            cout << "  " << (i + 1) << ". " << inventory[i]->getName() << endl;
        }
    }

    cout << "===============================" << endl;
}

// Method overloading for attack with specific ability
void Player::attack(Character& target, int abilityIndex) {
    if (!isAlive) {
        cout << name << " cannot attack because they are defeated!" << endl;
        return;
    }

    if (abilityIndex < 0 || abilityIndex >= static_cast<int>(abilities.size())) {
        cout << "Invalid ability index!" << endl;
        return;
    }

    // Use the specified ability
    abilities[abilityIndex]->use(*this, target);
}

// Method overloading for attack with ability by name
void Player::attack(Character& target, const string& abilityName) {
    if (!isAlive) {
        cout << name << " cannot attack because they are defeated!" << endl;
        return;
    }

    // Find ability by name
    auto it = find_if(abilities.begin(), abilities.end(),
        [&abilityName](const unique_ptr<Ability>& ability) {
            return ability->getName() == abilityName;
        });

    if (it != abilities.end()) {
        // Use the found ability
        (*it)->use(*this, target);
    }
    else {
        cout << "Ability '" << abilityName << "' not found!" << endl;
        // Fall back to regular attack
        attack(target);
    }
}

// Player-specific methods
void Player::levelUp() {
    level++;

    // Increase stats
    int healthIncrease = 20 + (level * 5);
    int meleeIncrease = 5 + (level * 2);
    int rangedIncrease = 3 + (level * 2);
    int defenceIncrease = 2 + level;

    setMaxHealth(maxHealth + healthIncrease);
    setCurrentHealth(maxHealth); // Heal to full on level up
    setMeleeDamage(meleeDamage + meleeIncrease);
    setRangedDamage(rangedDamage + rangedIncrease);
    setDefence(defence + defenceIncrease);

    cout << "\n🌟 LEVEL UP! 🌟" << endl;
    cout << name << " is now level " << level << "!" << endl;
    cout << "Max Health increased by " << healthIncrease << " to " << maxHealth << "!" << endl;
    cout << "Melee Damage increased by " << meleeIncrease << " to " << meleeDamage << "!" << endl;
    cout << "Ranged Damage increased by " << rangedIncrease << " to " << rangedDamage << "!" << endl;
    cout << "Defence increased by " << defenceIncrease << " to " << defence << "!" << endl;
}

void Player::addAbility(unique_ptr<Ability> ability) {
    cout << "\n✨ NEW ABILITY UNLOCKED! ✨" << endl;
    cout << "You have learned: " << ability->getName() << endl;
    cout << ability->getDescription() << " (" << ability->getActivationChance() << "% chance)" << endl;

    abilities.push_back(move(ability));
}

void Player::addItem(unique_ptr<Item> item) {
    cout << "\n🎁 NEW ITEM ACQUIRED! 🎁" << endl;
    cout << "You have obtained: " << item->getName() << endl;

    // Use the item immediately to apply its effects
    item->use();

    // Store in inventory
    inventory.push_back(move(item));
}

void Player::useItem(int index) {
    if (index < 0 || index >= static_cast<int>(inventory.size())) {
        cout << "Invalid item index!" << endl;
        return;
    }

    inventory[index]->use();
}

void Player::useItem(const string& itemName) {
    auto it = find_if(inventory.begin(), inventory.end(),
        [&itemName](const unique_ptr<Item>& item) {
            return item->getName() == itemName;
        });

    if (it != inventory.end()) {
        (*it)->use();
    }
    else {
        cout << "Item '" << itemName << "' not found in inventory!" << endl;
    }
}

void Player::listAbilities() const {
    if (abilities.empty()) {
        cout << "You have no special abilities yet." << endl;
        return;
    }

    cout << "\nSpecial Abilities:" << endl;
    for (size_t i = 0; i < abilities.size(); ++i) {
        cout << (i + 1) << ". " << abilities[i]->getName()
            << " - " << abilities[i]->getDescription()
            << " (" << abilities[i]->getActivationChance() << "% chance)" << endl;
    }
}

void Player::listInventory() const {
    if (inventory.empty()) {
        cout << "Your inventory is empty." << endl;
        return;
    }

    cout << "\nInventory:" << endl;
    for (size_t i = 0; i < inventory.size(); ++i) {
        cout << (i + 1) << ". " << inventory[i]->getName() << endl;
    }
}

// Getters
int Player::getLevel() const {
    return level;
}

bool Player::getBlockNextAttack() const {
    return blockNextAttack;
}

bool Player::getDodgeNextAttack() const {
    return dodgeNextAttack;
}

// Setters
void Player::setBlockNextAttack(bool status) {
    blockNextAttack = status;
}

void Player::setDodgeNextAttack(bool status) {
    dodgeNextAttack = status;
}

// Method to check and trigger abilities based on probability
bool Player::tryActivateAbility(Character& target) {
    if (abilities.empty()) {
        return false;
    }

    // Check each ability for activation
    for (auto& ability : abilities) {
        if (ability->checkActivation()) {
            // Activate the ability
            ability->use(*this, target);

            // Handle specific abilities' side effects
            if (ability->getName() == "Blocker") {
                blockNextAttack = true;
            }
            else if (ability->getName() == "Ranged Attack") {
                dodgeNextAttack = true;
            }

            return true; // An ability was activated
        }
    }

    return false; // No ability was activated
}