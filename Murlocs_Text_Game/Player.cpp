// player.cpp
#include "player.h"
#include <iostream>
#include <algorithm>

// Constructor implementation
Player::Player(const std::string& name)
    : Character(name, 100, 15, 10, 5), level(1), blockNextAttack(false), dodgeNextAttack(false) {
}

// Override methods from Character
void Player::attack(Character& target) {
    if (!isAlive) {
        std::cout << name << " cannot attack because they are defeated!" << std::endl;
        return;
    }

    // Try to activate a special ability first
    if (tryActivateAbility(target)) {
        return; // Ability was activated and used
    }

    // Regular attack if no ability was activated
    int damage = meleeDamage;
    std::cout << name << " attacks " << target.getName() << " for " << damage << " damage!" << std::endl;
    target.takeDamage(damage);
}

void Player::takeDamage(int damage) {
    if (!isAlive) return;

    // Check if block or dodge is active
    if (blockNextAttack) {
        std::cout << name << " blocks the attack completely!" << std::endl;
        blockNextAttack = false; // Reset block status
        return;
    }

    if (dodgeNextAttack) {
        std::cout << name << " dodges the attack completely!" << std::endl;
        dodgeNextAttack = false; // Reset dodge status
        return;
    }

    // Calculate actual damage after defense
    int actualDamage = calculateDamage(damage);
    std::cout << name << " takes " << actualDamage << " damage!" << std::endl;

    // Update health
    setCurrentHealth(currentHealth - actualDamage);

    // Check if player is defeated
    if (currentHealth <= 0) {
        isAlive = false;
        std::cout << name << " has been defeated!" << std::endl;
    }
}

void Player::heal(int amount) {
    if (!isAlive) {
        std::cout << name << " cannot heal because they are defeated!" << std::endl;
        return;
    }

    int oldHealth = currentHealth;
    setCurrentHealth(currentHealth + amount);
    int actualHeal = currentHealth - oldHealth;

    std::cout << name << " heals for " << actualHeal << " health points!" << std::endl;
    std::cout << "Health: " << currentHealth << "/" << maxHealth << std::endl;
}

void Player::displayStats() const {
    std::cout << "\n===== " << name << "'s Stats (Level " << level << ") =====" << std::endl;
    std::cout << "Health: " << currentHealth << "/" << maxHealth << std::endl;
    std::cout << "Melee Damage: " << meleeDamage << std::endl;
    std::cout << "Ranged Damage: " << rangedDamage << std::endl;
    std::cout << "Defence: " << defence << std::endl;

    // Display abilities if any
    if (!abilities.empty()) {
        std::cout << "\nSpecial Abilities:" << std::endl;
        for (size_t i = 0; i < abilities.size(); ++i) {
            std::cout << "  " << (i + 1) << ". " << abilities[i]->getName()
                << " - " << abilities[i]->getDescription()
                << " (" << abilities[i]->getActivationChance() << "% chance)" << std::endl;
        }
    }

    // Display inventory if any
    if (!inventory.empty()) {
        std::cout << "\nInventory:" << std::endl;
        for (size_t i = 0; i < inventory.size(); ++i) {
            std::cout << "  " << (i + 1) << ". " << inventory[i]->getName() << std::endl;
        }
    }

    std::cout << "===============================" << std::endl;
}

// Method overloading for attack with specific ability
void Player::attack(Character& target, int abilityIndex) {
    if (!isAlive) {
        std::cout << name << " cannot attack because they are defeated!" << std::endl;
        return;
    }

    if (abilityIndex < 0 || abilityIndex >= static_cast<int>(abilities.size())) {
        std::cout << "Invalid ability index!" << std::endl;
        return;
    }

    // Use the specified ability
    abilities[abilityIndex]->use(*this, target);
}

// Method overloading for attack with ability by name
void Player::attack(Character& target, const std::string& abilityName) {
    if (!isAlive) {
        std::cout << name << " cannot attack because they are defeated!" << std::endl;
        return;
    }

    // Find ability by name
    auto it = std::find_if(abilities.begin(), abilities.end(),
        [&abilityName](const std::unique_ptr<Ability>& ability) {
            return ability->getName() == abilityName;
        });

    if (it != abilities.end()) {
        // Use the found ability
        (*it)->use(*this, target);
    }
    else {
        std::cout << "Ability '" << abilityName << "' not found!" << std::endl;
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

    std::cout << "\n🌟 LEVEL UP! 🌟" << std::endl;
    std::cout << name << " is now level " << level << "!" << std::endl;
    std::cout << "Max Health increased by " << healthIncrease << " to " << maxHealth << "!" << std::endl;
    std::cout << "Melee Damage increased by " << meleeIncrease << " to " << meleeDamage << "!" << std::endl;
    std::cout << "Ranged Damage increased by " << rangedIncrease << " to " << rangedDamage << "!" << std::endl;
    std::cout << "Defence increased by " << defenceIncrease << " to " << defence << "!" << std::endl;
}

void Player::addAbility(std::unique_ptr<Ability> ability) {
    std::cout << "\n✨ NEW ABILITY UNLOCKED! ✨" << std::endl;
    std::cout << "You have learned: " << ability->getName() << std::endl;
    std::cout << ability->getDescription() << " (" << ability->getActivationChance() << "% chance)" << std::endl;

    abilities.push_back(std::move(ability));
}

void Player::addItem(std::unique_ptr<Item> item) {
    std::cout << "\n🎁 NEW ITEM ACQUIRED! 🎁" << std::endl;
    std::cout << "You have obtained: " << item->getName() << std::endl;

    // Use the item immediately to apply its effects
    item->use();

    // Store in inventory
    inventory.push_back(std::move(item));
}

void Player::useItem(int index) {
    if (index < 0 || index >= static_cast<int>(inventory.size())) {
        std::cout << "Invalid item index!" << std::endl;
        return;
    }

    inventory[index]->use();
}

void Player::useItem(const std::string& itemName) {
    auto it = std::find_if(inventory.begin(), inventory.end(),
        [&itemName](const std::unique_ptr<Item>& item) {
            return item->getName() == itemName;
        });

    if (it != inventory.end()) {
        (*it)->use();
    }
    else {
        std::cout << "Item '" << itemName << "' not found in inventory!" << std::endl;
    }
}

void Player::listAbilities() const {
    if (abilities.empty()) {
        std::cout << "You have no special abilities yet." << std::endl;
        return;
    }

    std::cout << "\nSpecial Abilities:" << std::endl;
    for (size_t i = 0; i < abilities.size(); ++i) {
        std::cout << (i + 1) << ". " << abilities[i]->getName()
            << " - " << abilities[i]->getDescription()
            << " (" << abilities[i]->getActivationChance() << "% chance)" << std::endl;
    }
}

void Player::listInventory() const {
    if (inventory.empty()) {
        std::cout << "Your inventory is empty." << std::endl;
        return;
    }

    std::cout << "\nInventory:" << std::endl;
    for (size_t i = 0; i < inventory.size(); ++i) {
        std::cout << (i + 1) << ". " << inventory[i]->getName() << std::endl;
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