// item.cpp
#include "item.h"

// Base Item class implementation
Item::Item(const std::string& name, const std::string& desc)
    : name(name), description(desc) {
}

std::string Item::getName() const {
    return name;
}

std::string Item::getDescription() const {
    return description;
}

void Item::displayInfo() const {
    std::cout << "Item: " << name << std::endl;
    std::cout << "Description: " << description << std::endl;
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
    std::cout << "You raise the " << name << " high, feeling its power coursing through you!" << std::endl;
    std::cout << "Melee damage increased by " << damageBoost << "!" << std::endl;
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
    std::cout << "You strap the " << name << " to your arm, feeling more protected!" << std::endl;
    std::cout << "Defence increased by " << defenceBoost << "!" << std::endl;
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
    std::cout << "You don the " << name << ", feeling its protective embrace!" << std::endl;
    std::cout << "Maximum health increased by " << healthBoost << "!" << std::endl;
    std::cout << "Defence increased by " << defenceBoost << "!" << std::endl;
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
    std::cout << "You string the " << name << ", feeling its precision and power!" << std::endl;
    std::cout << "Ranged damage increased by " << rangedDamageBoost << "!" << std::endl;
}

// Map item implementation
Map::Map()
    : Item("Ancient Map", "A weathered map showing the path to defeat Murlocs") {
}

void Map::use() const {
    std::cout << "You unfold the " << name << " and study it carefully..." << std::endl;
    std::cout << "The map reveals a long journey ahead. You must collect four magical items:" << std::endl;
    std::cout << "- The Legendary Sword (Level 2)" << std::endl;
    std::cout << "- The Defender Shield (Level 3)" << std::endl;
    std::cout << "- The Guardian Armor (Level 4)" << std::endl;
    std::cout << "- The Hunter's Bow (Level 5)" << std::endl;
    std::cout << "Only with these items can you hope to defeat Murlocs and save your village!" << std::endl;
}