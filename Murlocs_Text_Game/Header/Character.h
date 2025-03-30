// character.h
#ifndef CHARACTER_H
#define CHARACTER_H


#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;

class Character {
protected:
	string name;
	int maxHealth;
	int meleeDamage;
	int currentHealth;
	int rangedDamage;
	int defence;
	bool isAlive;


	// RNG for probability-based events
	static random_device rd;
	static mt19937 gen;
	static uniform_int_distribution<int> dis;

public:
	//const
	Character(const string& name, int health, int melee, int ranged, int def);

	//destructor
	~Character() {

	}

	//getters
	string getName() const;
	int getMaxHealth() const;
	int getCurrentHealth() const;
	int getMeleeDamage() const;
	int getRangedDamage() const;
	int getDefence() const;
	bool getIsAlive() const;

	// Setters (with validation)
	void setName(const string& newName);
	void setMaxHealth(int health);
	void setCurrentHealth(int health);
	void setMeleeDamage(int damage);
	void setRangedDamage(int damage);
	void setDefence(int def);

	//calculate the actual damage
	virtual int calculateDamage(int rawDamage) const;

	// Pure virtual methods --will have to be override
	virtual void attack(Character& target) = 0;
	virtual void takeDamage(int damage) = 0;
	virtual void heal(int amount) = 0;
	virtual void displayStats() const = 0;

	// Method to check if character is alive
	bool checkIsAlive();

	//static method to generate random number
	static int getRandomNumber(int min, int max);
};

#endif