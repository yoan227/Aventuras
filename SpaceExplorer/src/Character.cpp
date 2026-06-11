//
// Created by zunig on 6/11/2026.
//

#include "Character.h"
#include <algorithm>
#include <sstream>

Character::Character(const std::string& name, int health, int oxygen)
    : name(name), health(health), oxygen(oxygen),
      maxHealth(health), maxOxygen(oxygen) {}

std::string Character::getName() const { return name; }
int Character::getHealth() const { return health; }
int Character::getOxygen() const { return oxygen; }
bool Character::isAlive() const { return health > 0 && oxygen > 0; }

void Character::applyHealthEffect(int amount) {
    health = std::max(0, std::min(maxHealth, health + amount));
}

void Character::applyOxygenEffect(int amount) {
    oxygen = std::max(0, std::min(maxOxygen, oxygen + amount));
}

void Character::pickUpItem(std::shared_ptr<Item> item) {
    inventory.push_back(item);
}

const std::vector<std::shared_ptr<Item>>& Character::getInventory() const {
    return inventory;
}

bool Character::hasItemOfType(Item::Type type) const {
    for (const auto& item : inventory) {
        if (item->getType() == type) return true;
    }
    return false;
}

// Operator+= applies the item effect to the character stats
Character& Character::operator+=(std::shared_ptr<Item> item) {
    switch (item->getType()) {
        case Item::Type::OXYGEN:
            applyOxygenEffect(item->getValue());
            break;
        case Item::Type::MEDKIT:
            applyHealthEffect(item->getValue());
            break;
        default:
            // Keys, weapons, artifacts go to inventory only
            break;
    }
    pickUpItem(item);
    return *this;
}

std::string Character::statusSummary() const {
    std::ostringstream oss;
    oss << name
        << " | HP: " << health << "/" << maxHealth
        << " | O2: " << oxygen << "/" << maxOxygen
        << " | Items: " << inventory.size();
    return oss.str();
}
