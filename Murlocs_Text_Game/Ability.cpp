#include "Header/Ability.h"
#include <iostream>
using namespace std;

//base ability class implementation
Ability::Ability(const string& name, const string& desc, int chance)
	: name(name), description(desc), activationChance(chance) {
}

string Ability::getName() const {
		return name;
}

string Ability::getDescription() const {
	return description;
}
int Ability::getActivationChance() const {
	return activationChance;
}
//Check if ability activates based on probability
bool Ability::checkActivation() const {
	return (Character::getRandomNumber(1, 100) <= activationChance);
}

CriticalHit::CriticalHit(float multiplier) : Ability("Critical Hit", "Performs attack with massive damage boost", 10),
damageMultiplier(multiplier) {

}
void CriticalHit::use(Character& user, Character& target) {
	int baseDamage = user.getMeleeDamage();
	int criticalDamage = static_cast<int>(baseDamage * damageMultiplier);

	cout << "\n CRITICAL HIT! " << user.getName() << " deals " << criticalDamage << " damage!" << endl;

	target.takeDamage(criticalDamage);
}
//blocker ability
Blocker::Blocker() : Ability("Blocker", "Blocks all damage from enemy's next attack", 10) {

}

void Blocker::use(Character& user, Character& target) {
	// This is a passive ability that will be checked in the Player's takeDamage method
	cout << "\n PERFECT BLOCK! " << user.getName() << " completely blocks ";
}

//lifesteal ability implementation
LifeSteal::LifeSteal(float percentage) : Ability("Life Steal", "Recover health equal to a percentage of damage dealt", 10),
stealPercentage(percentage) {

}

void LifeSteal::use(Character& user, Character& target) {
	int damageDealt = target.calculateDamage(user.getMeleeDamage());
	int healthStolen = static_cast<int>(damageDealt * stealPercentage);

	cout << "\n LIFE STEAL! " << user.getName() << " steals " << healthStolen << " health!" << endl;

	target.takeDamage(damageDealt);
	user.heal(healthStolen);

}

RangedAttack::RangedAttack() : Ability("Ranged Attack", "Attack from distance and avoid next enemy attack", 10),
dodgeNextAttack(false) {

}
void RangedAttack::use(Character& user, Character& target) {
	int damage = user.getRangedDamage();

	cout << "\n RANGED ATTACK@! " << user.getName() << " attacks from a distance for "
		<< damage << " damage and will dodge the next attack!" << endl;

	target.takeDamage(damage);
	dodgeNextAttack = true;
}

bool RangedAttack::getDodgeNextAttack() const {
	return dodgeNextAttack;
}

void RangedAttack::setDodgeNextAttack(bool status) {
	dodgeNextAttack = status;
}