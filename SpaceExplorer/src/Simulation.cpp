//
// Created by zunig on 6/11/2026.
//

#include "Simulation.h"
#include <queue>
#include <set>
#include <sstream>

Simulation::Simulation(std::shared_ptr<World> world,
                       std::shared_ptr<Character> character,
                       std::shared_ptr<Logger> logger)
    : world(world), character(character), logger(logger), won(false) {}

// -----------------------------------------------------------------------
// Main simulation loop: BFS traversal of the world graph.
// The character visits each room once. The simulation ends when:
//   - The character reaches the EXIT room (win), or
//   - The character runs out of health or oxygen (lose), or
//   - All reachable rooms have been visited (lose by exhaustion)
// -----------------------------------------------------------------------
void Simulation::run() {
    logger->log("=== Simulation started ===");
    logger->log("Astronaut " + character->getName() + " wakes up aboard the derelict ship.");

    std::queue<std::shared_ptr<Room>> frontier;
    std::set<std::string> visited;

    auto start = world->getStartRoom();
    frontier.push(start);

    while (!frontier.empty() && character->isAlive()) {
        auto current = frontier.front();
        frontier.pop();

        if (visited.count(current->getId())) continue;
        visited.insert(current->getId());

        enterRoom(current);
        processItems(current);
        processEvents(current);

        if (current->isExit()) {
            logger->log(">> " + character->getName() +
                        " reaches the BRIDGE and activates the escape pod!");
            won = true;
            break;
        }

        if (!character->isAlive()) break;

        // Enqueue unvisited neighbors
        for (const auto& neighborId : current->getConnections()) {
            if (!visited.count(neighborId)) {
                frontier.push(world->getRoom(neighborId));
            }
        }
    }

    if (!character->isAlive()) {
        logger->log(">> " + character->getName() + " has been lost in the void.");
    } else if (!won) {
        logger->log(">> All sections explored. No escape route found. Mission failed.");
    }

    logger->log("=== Simulation ended ===");
    logger->log(character->statusSummary());
}

bool Simulation::didWin() const { return won; }

void Simulation::enterRoom(std::shared_ptr<Room> room) {
    room->markVisited();
    std::ostringstream oss;
    oss << "Entering: " << *room << " - " << room->getDescription();
    logger->log(oss.str());
}

void Simulation::processItems(std::shared_ptr<Room> room) {
    auto& items = room->getItems();
    for (auto& item : items) {
        std::ostringstream oss;
        oss << "  Found item: [" << item->typeToString() << "] "
            << item->getName() << " (value: " << item->getValue() << ")";

        // Use operator+= to apply item effects
        *character += item;

        if (item->getType() == Item::Type::OXYGEN ||
            item->getType() == Item::Type::MEDKIT) {
            oss << " -> applied to character";
        } else {
            oss << " -> added to inventory";
        }
        logger->log(oss.str());
        logger->log("  Status: " + character->statusSummary());
    }
}

void Simulation::processEvents(std::shared_ptr<Room> room) {
    auto& events = room->getEvents();
    for (auto& event : events) {
        if (event->isTriggered()) continue;
        event->markTriggered();

        std::ostringstream oss;
        oss << "  EVENT [" << event->getTypeName() << "]: "
            << event->getDescription();
        logger->log(oss.str());

        int hpEffect = event->healthEffect();
        int o2Effect = event->oxygenEffect();

        // If character has a weapon, reduce enemy damage by half
        if (event->getTypeName() == "ENEMY" &&
            character->hasItemOfType(Item::Type::WEAPON)) {
            hpEffect /= 2;
            logger->log("  [WEAPON BONUS] Damage reduced by weapon in inventory.");
        }

        character->applyHealthEffect(hpEffect);
        character->applyOxygenEffect(o2Effect);

        if (hpEffect != 0) {
            oss.str("");
            oss << "  HP effect: " << hpEffect
                << " -> HP now: " << character->getHealth();
            logger->log(oss.str());
        }
        if (o2Effect != 0) {
            oss.str("");
            oss << "  O2 effect: " << o2Effect
                << " -> O2 now: " << character->getOxygen();
            logger->log(oss.str());
        }

        logger->log("  Status: " + character->statusSummary());

        if (!character->isAlive()) break;
    }
}