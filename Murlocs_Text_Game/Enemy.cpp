// enemy.cpp
#include "Header/Enemy.h"
#include <iostream>
#include <vector>
using namespace std;

// Enemy implementation
Enemy::Enemy(const string& name, int health, int meleeAtk, int rangedAtk, int def, int expReward)
	: Character(name, health, meleeAtk, rangedAtk, def), experienceReward(expReward) {
}

void Enemy::attack(Character& target) {
	if (!isAlive) {
		return;
	}

	// Random chance to use melee or ranged attack
	bool useMelee = (getRandomNumber(1, 2) == 1);
	int damage = useMelee ? meleeDamage : rangedDamage;

	cout << name << " attacks " << target.getName();
	if (useMelee) {
		cout << " with a melee strike for " << damage << " damage!" << endl;
	}
	else {
		cout << " with a ranged attack for " << damage << " damage!" << endl;
	}

	target.takeDamage(damage);
}

void Enemy::takeDamage(int damage) {
	if (!isAlive) return;

	// Calculate actual damage after defense
	int actualDamage = calculateDamage(damage);
	cout << name << " takes " << actualDamage << " damage!" << endl;

	// Update health
	setCurrentHealth(currentHealth - actualDamage);

	// Check if enemy is defeated
	if (currentHealth <= 0) {
		isAlive = false;
		cout << name << " has been defeated!" << endl;
	}
}

void Enemy::heal(int amount) {
	if (!isAlive) return;

	int oldHealth = currentHealth;
	setCurrentHealth(currentHealth + amount);
	int actualHeal = currentHealth - oldHealth;

	cout << name << " regenerates " << actualHeal << " health points!" << endl;
}

void Enemy::displayStats() const {
	cout << "\n--- " << name << " Stats ---" <<  endl;
	cout << "Health: " << currentHealth << "/" << maxHealth << endl;
	cout << "Melee Attack: " << meleeDamage << endl;
	cout << "Ranged Attack: " << rangedDamage << endl;
	cout << "Defence: " << defence << endl;
	cout << "-------------------" << endl;
}

int Enemy::getExperienceReward() const {
	return experienceReward;
}

string Enemy::generateEnemyName() {
	static const vector<string> prefixes = {
		"Dark", "Shadow", "Feral", "Savage", "Vicious", "Undead", "Corrupted", "Vengeful", "Rabid", "Wild"
	};

	static const vector<string> creatures = {
		"Wolf", "Goblin", "Orc", "Troll", "Zombie", "Skeleton", "Bandit", "Cultist", "Wraith", "Beast"
	};

	string prefix = prefixes[getRandomNumber(0, prefixes.size() - 1)];
	string creature = creatures[getRandomNumber(0, creatures.size() - 1)];

	return prefix + " " + creature;
}

// Boss implementation
Boss::Boss(const string& name, int health, int meleeAtk, int rangedAtk, int def, int expReward)
	: Enemy(name, health, meleeAtk, rangedAtk, def, expReward), specialAttackDamage(meleeAtk * 2) {
	// Add default special attacks
	addSpecialAttack("Ground Slash");
	addSpecialAttack("Speed Dash");
	addSpecialAttack("Health Regeneration");
}

void Boss::attack(Character& target) {
	if (!isAlive) return;

	// 40% chance to use special attack
	if (getRandomNumber(1, 100) <= 40 && !specialAttacks.empty()) {
		// Randomly choose a special attack
		int attackIndex = getRandomNumber(0, specialAttacks.size() - 1);
		useSpecialAttack(target, attackIndex);
	}
	else {
		// Use regular attack
		Enemy::attack(target);
	}
}

void Boss::takeDamage(int damage) {
	if (!isAlive) return;

	// Calculate actual damage after defense
	int actualDamage = calculateDamage(damage);
	cout << name << " takes " << actualDamage << " damage!" << endl;

	// Update health
	setCurrentHealth(currentHealth - actualDamage);

	// 20% chance to trigger health regeneration when below 50% health
	if (currentHealth <= maxHealth / 2 && getRandomNumber(1, 100) <= 20) {
		int healAmount = maxHealth * 0.1; // Heal 10% of max health
		cout << "\n💚 " << name << " uses Health Regeneration!" << endl;
		heal(healAmount);
	}

	// Check if boss is defeated
	if (currentHealth <= 0) {
		isAlive = false;
		cout << name << " has been defeated!" << endl;
	}
}

void Boss::addSpecialAttack(const string& attackName) {
	specialAttacks.push_back(attackName);
}

void Boss::useSpecialAttack(Character& target, int attackIndex) {
	if (attackIndex < 0 || attackIndex >= static_cast<int>(specialAttacks.size())) {
		// Fall back to regular attack if invalid index
		Enemy::attack(target);
		return;
	}

	string attackName = specialAttacks[attackIndex];

	cout << "\n⚡ " << name << " uses " << attackName << "!" << endl;

	if (attackName == "Ground Slash") {
		// Ground Slash: Higher damage but slower
		int damage = specialAttackDamage * 1.5;
		cout << "A devastating wave of energy tears through the ground towards "
			<< target.getName() << " for " << damage << " damage!" << endl;
		target.takeDamage(damage);
	}
	else if (attackName == "Speed Dash") {
		// Speed Dash: Multiple hits with lower damage
		int hitCount = getRandomNumber(2, 4);
		int damagePerHit = specialAttackDamage / 2;

		cout << name << " dashes at incredible speed, striking "
			<< target.getName() << " " << hitCount << " times!" << endl;

		for (int i = 0; i < hitCount; ++i) {
			cout << "Hit " << (i + 1) << ": " << damagePerHit << " damage!" << endl;
			target.takeDamage(damagePerHit);
		}
	}
	else if (attackName == "Health Regeneration") {
		// Health Regeneration: Heal a significant amount
		int healAmount = maxHealth * 0.2; // Heal 20% of max health
		cout << name << " channels dark energy to regenerate "
			<< healAmount << " health!" << endl;
		heal(healAmount);

		// Also perform a weaker attack
		int damage = specialAttackDamage / 2;
		cout << "While regenerating, " << name << " strikes at "
			<< target.getName() << " for " << damage << " damage!" << endl;
		target.takeDamage(damage);
	}
	else {
		// Generic special attack for any new abilities added
		cout << "The attack deals " << specialAttackDamage << " damage to "
			<< target.getName() << "!" << endl;
		target.takeDamage(specialAttackDamage);
	}
}

int Boss::getSpecialAttackCount() const {
	return specialAttacks.size();
}

void Boss::displayStats() const {
	// Call the base class method
	Enemy::displayStats();
}

// Method overloading for demonstration
void Boss::displayStats(bool showSpecialAttacks) const {
	// Call the base version first
	displayStats();

	// Optionally show special attacks
	if (showSpecialAttacks && !specialAttacks.empty()) {
		cout << "\nSpecial Attacks:" << endl;
		for (size_t i = 0; i < specialAttacks.size(); ++i) {
			cout << "  " << (i + 1) << ". " << specialAttacks[i] << endl;
		}
	}
}