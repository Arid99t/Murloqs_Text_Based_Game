#include "Header/Character.h"
using namespace std;


// Initialize static members
random_device Character::rd;
mt19937 Character::gen(Character::rd());
uniform_int_distribution<int> Character::dis(1, 100);

//constructor
Character::Character(const string& name, int health, int melee, int ranged, int def)
	: name(name), maxHealth(health), currentHealth(health), meleeDamage(melee), rangedDamage(ranged), defence(def), isAlive(true) {

}


// Getters implementation

string Character::getName() const {
	return name;
}
int Character::getMaxHealth() const {
	return maxHealth;
}
int Character::getCurrentHealth() const {
	return currentHealth;
}
int Character::getMeleeDamage() const {
	return meleeDamage;
}

int Character::getRangedDamage() const {
	return rangedDamage;
}

int Character::getDefence() const {
	return defence;
}
bool Character::getIsAlive() const {
	return isAlive;
}

//Setters implementation

void Character::setName(const string& newName) {
	name = newName;
}

void Character::setMaxHealth(int health) {
	if (health > 0) {
		maxHealth = health;

		if (currentHealth > maxHealth) {
			currentHealth = maxHealth;
		}
	}
}
void Character::setCurrentHealth(int health) {
	if (health < 0) {
		currentHealth = health;
		isAlive = false;
	}
	else if (health > maxHealth) {
		currentHealth = maxHealth;
	}
	else {
		currentHealth = health;
	}
}
void Character::setMeleeDamage(int damage) {
	if (damage >= 0) {
		meleeDamage = damage;
	}
}

void Character::setRangedDamage(int damage) {
	if (damage >= 0) {
		rangedDamage = damage;
	}
}

void Character::setDefence(int def) {
	if (def >= 0) {
		defence = def;
	}
}

//calculate damage after defence
int Character::calculateDamage(int rawDamage) const {
	int actualDamage = rawDamage - defence;
	return (actualDamage > 0) ? actualDamage : 1; //min damage will be 1
}

bool Character::checkIsAlive() {
	if (currentHealth > 0) {
		isAlive = true;
	}
	else {
		isAlive = false;
	}
	return isAlive;
}

//bool Character::checkIsAlive() {
//	isAlive = (currentHealth > 0);
//	return isAlive;
//}


int Character::getRandomNumber(int min, int max) {
	uniform_int_distribution<int> distribution(min, max);
	return distribution(gen);
}