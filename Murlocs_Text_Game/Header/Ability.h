// ability.h
#ifndef ABILITY_H
#define ABILITY_H

#include "Header/Character.h"
#include <string>
#include <memory>

using namespace std;

class Ability {
protected:
	string name;
	string description;
	int activationChance; //Probability out of 100


public:
	
	//constructor
	Ability(const string& name, const string& desc, int chance);

	//virtual destructor
	virtual ~Ability() = default;

	//getters
	string getName() const;
	string getDescription() const;
	int getActivationChance() const;


	//Check if ability activates based on probability
	bool checkActivation() const;

	//pure virtual method to use the ability
	virtual void use(Character& user, Character& target) = 0;

};

//criticalHit ability (awared at level 2)
class CriticalHit : public Ability {
private:
	float damageMultiplier;

public: 
	//constructor
	CriticalHit(float multiplier = 2.0f);

	//override use method
	void use(Character& user, Character& target) override;
};

//blocker ability (awarded at level 3)

class Blocker : public Ability {
public: 
	//constructor
	Blocker();

	//override use method
	void use(Character& user, Character& target) override;
};

//lifesteal ability ( at level 4)
class LifeSteal : public Ability {
private:
	float stealPercentage;

public:
	//constructor
	LifeSteal(float percentage = 0.3f);

	//override
	void use(Character& user, Character& target) override;
};

//ranngedAttack ability (level 5)
class RangedAttack : public Ability {
private:
	bool dodgeNextAttack;

public:
	//constructor
	RangedAttack();

	//override 
	void use(Character& user, Character& target) override;

	//Getter for dodge status
	bool getDodgeNextAttack() const;

	//setter for dodge status
	void setDodgeNextAttack(bool status);
};

#endif 