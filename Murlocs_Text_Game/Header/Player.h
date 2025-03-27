#pragma once

#include "character.h"
#include "ability.h"
#include "item.h"
#include <vector>
#include <memory>
using namespace std;

class Player : public Character {
private:
	int level;
	vector<unique_ptr<Ability>> abilities;
	vector<unique_ptr<Item>> inventory;
	bool blockNextAttack; //blocker ability
	bool dodgeNextAttack; //ranged atk ability

public:
	//constructor
	Player(const string& name);

	//override virtual methods from character
	void attack(Character& target) override;
	void takeDamage(int damage) override;
	void heal(int amount) override;
	void displayStats() const override;


	//attack with spc ability
	void attack(Character& target, int abilityIndex);

	void attack(Character& target, const string& abilityName);

	//Player specific methods
	void levelUp();
	void addAbility(unique_ptr<Ability> ability);
	void addItem(unique_ptr<Item> item);
	void useIteam(int index);
	void useIteam(const string& itemName);
	void listAbilities() const;
	void listInventory() const;

	//getters
	int getLevel() const;
	bool getBlockNextAttack() const;
	bool getDodgeNextAttack() const;

	//setters
	void setBlockNextAttack(bool status);
	void setDodgeNextAttack(bool status);

	//method to check and trigger abilities based on probability
	bool tryActivateAbility(Character& target);
};