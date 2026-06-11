//
// Created by zunig on 6/11/2026.
//

#define AVENTURAS_CHARACTER_H


#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <memory>
#include "Item.h"

// Represents the astronaut exploring the spaceship
class Character {
public:
    Character(const std::string& name, int health, int oxygen);

    std::string getName() const;
    int getHealth() const;
    int getOxygen() const;
    bool isAlive() const;

    void applyHealthEffect(int amount);  // positive = heal, negative = damage
    void applyOxygenEffect(int amount);  // positive = refill, negative = drain

    void pickUpItem(std::shared_ptr<Item> item);
    const std::vector<std::shared_ptr<Item>>& getInventory() const;
    bool hasItemOfType(Item::Type type) const;

    // Overloaded += to apply an item effect directly to the character
    Character& operator+=(std::shared_ptr<Item> item);

    std::string statusSummary() const;

private:
    std::string name;
    int health;
    int oxygen;
    int maxHealth;
    int maxOxygen;
    std::vector<std::shared_ptr<Item>> inventory;
};


#endif
