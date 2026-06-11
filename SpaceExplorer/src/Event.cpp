//
// Created by zunig on 6/11/2026.
//

#include "Event.h"

// ---- Base ----
Event::Event(const std::string& id, const std::string& description)
    : id(id), description(description), triggered(false) {}

std::string Event::getId() const { return id; }
std::string Event::getDescription() const { return description; }
bool Event::isTriggered() const { return triggered; }
void Event::markTriggered() { triggered = true; }

// ---- EnemyEvent ----
EnemyEvent::EnemyEvent(const std::string& id, const std::string& description, int damage)
    : Event(id, description), damage(damage) {}

int EnemyEvent::healthEffect() const { return -damage; }
int EnemyEvent::oxygenEffect() const { return 0; }
std::string EnemyEvent::getTypeName() const { return "ENEMY"; }

// ---- HazardEvent ----
HazardEvent::HazardEvent(const std::string& id, const std::string& description, int oxygenDrain)
    : Event(id, description), oxygenDrain(oxygenDrain) {}

int HazardEvent::healthEffect() const { return 0; }
int HazardEvent::oxygenEffect() const { return -oxygenDrain; }
std::string HazardEvent::getTypeName() const { return "HAZARD"; }

// ---- BonusEvent ----
BonusEvent::BonusEvent(const std::string& id, const std::string& description,
                       int healthGain, int oxygenGain)
    : Event(id, description), healthGain(healthGain), oxygenGain(oxygenGain) {}

int BonusEvent::healthEffect() const { return healthGain; }
int BonusEvent::oxygenEffect() const { return oxygenGain; }
std::string BonusEvent::getTypeName() const { return "BONUS"; }
