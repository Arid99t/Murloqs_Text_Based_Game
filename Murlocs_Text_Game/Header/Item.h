// item.h
#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

// Abstract base class for all items
class Item {
protected:
    std::string name;
    std::string description;

public:
    // Constructor
    Item(const std::string& name, const std::string& desc);

    // Virtual destructor
    virtual ~Item() = default;

    // Getters
    std::string getName() const;
    std::string getDescription() const;

    // Pure virtual method to use the item (will be implemented by derived classes)
    virtual void use() const = 0;

    // Display item information
    virtual void displayInfo() const;
};

// Sword item (awarded at level 2)
class Sword : public Item {
private:
    int damageBoost;

public:
    // Constructor
    Sword(int boost = 10);

    // Getter for damage boost
    int getDamageBoost() const;

    // Override use method
    void use() const override;
};

// Shield item (awarded at level 3)
class Shield : public Item {
private:
    int defenceBoost;

public:
    // Constructor
    Shield(int boost = 8);

    // Getter for defence boost
    int getDefenceBoost() const;

    // Override use method
    void use() const override;
};

// Armor item (awarded at level 4)
class Armor : public Item {
private:
    int healthBoost;
    int defenceBoost;

public:
    // Constructor with two parameters (method overloading example)
    Armor(int hpBoost = 30, int defBoost = 5);

    // Getters
    int getHealthBoost() const;
    int getDefenceBoost() const;

    // Override use method
    void use() const override;
};

// Bow item (awarded at level 5)
class Bow : public Item {
private:
    int rangedDamageBoost;

public:
    // Constructor
    Bow(int boost = 15);

    // Getter for ranged damage boost
    int getRangedDamageBoost() const;

    // Override use method
    void use() const override;
};

// Map item (awarded at level 1)
class Map : public Item {
public:
    // Constructor
    Map();

    // Override use method
    void use() const override;
};

#endif // ITEM_H