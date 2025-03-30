// item.cpp
#include "Header/Item.h"
using namespace std;

// Base Item class implementation
Item::Item(const string& name, const string& desc)
    : name(name), description(desc) {
}

string Item::getName() const {
    return name;
}

string Item::getDescription() const {
    return description;
}

void Item::displayInfo() const {
    cout << "Item: " << name << endl;
    cout << "Description: " << description << endl;
}

// Sword item implementation
Sword::Sword(int boost)
    : Item("Legendary Sword", "An ancient blade that increases melee damage"),
    damageBoost(boost) {
}

int Sword::getDamageBoost() const {
    return damageBoost;
}

void Sword::use() const {
    cout << "You raise the " << name << " high, feeling its power coursing through you!" << endl;
    cout << "Melee damage increased by " << damageBoost << "!" << endl;
}

// Shield item implementation
Shield::Shield(int boost)
    : Item("Defender Shield", "A sturdy shield that enhances your defense"),
    defenceBoost(boost) {
}

int Shield::getDefenceBoost() const {
    return defenceBoost;
}

void Shield::use() const {
    cout << "You strap the " << name << " to your arm, feeling more protected!" << endl;
    cout << "Defence increased by " << defenceBoost << "!" << endl;
}

// Armor item implementation
Armor::Armor(int hpBoost, int defBoost)
    : Item("Guardian Armor", "Protective armor that increases both health and defense"),
    healthBoost(hpBoost), defenceBoost(defBoost) {
}

int Armor::getHealthBoost() const {
    return healthBoost;
}

int Armor::getDefenceBoost() const {
    return defenceBoost;
}

void Armor::use() const {
    cout << "You don the " << name << ", feeling its protective embrace!" << endl;
    cout << "Maximum health increased by " << healthBoost << "!" << endl;
    cout << "Defence increased by " << defenceBoost << "!" << endl;
}

// Bow item implementation
Bow::Bow(int boost)
    : Item("Hunter's Bow", "A finely crafted bow that enhances ranged attacks"),
    rangedDamageBoost(boost) {
}

int Bow::getRangedDamageBoost() const {
    return rangedDamageBoost;
}

void Bow::use() const {
    cout << "You string the " << name << ", feeling its precision and power!" << endl;
    cout << "Ranged damage increased by " << rangedDamageBoost << "!" << endl;
}

// Map item implementation
Map::Map()
    : Item("Ancient Map", "A weathered map showing the path to defeat Murlocs") {
}

void Map::use() const {
    cout << "You unfold the " << name << " and study it carefully..." << endl;
    cout << "The map reveals a long journey ahead. You must collect four magical items:" << endl;
    cout << "- The Legendary Sword (Level 2)" << endl;
    cout << "- The Defender Shield (Level 3)" << endl;
    cout << "- The Guardian Armor (Level 4)" << endl;
    cout << "- The Hunter's Bow (Level 5)" << endl;
    cout << "Only with these items can you hope to defeat Murlocs and save your village!" << endl;
}