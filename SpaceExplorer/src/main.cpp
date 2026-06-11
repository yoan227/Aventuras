//
// Created by zunig on 6/11/2026.
//
#include <iostream>
#include <memory>
#include <sstream>
#include "World.h"
#include "Character.h"
#include "Simulation.h"
#include "Logger.h"

int main() {
    try {
        // ---- Load world from data files ----
        auto world = std::make_shared<World>();
        world->loadRooms("data/rooms.txt");
        world->loadItems("data/items.txt");
        world->loadEvents("data/events.txt");

        // ---- Create the player character ----
        auto character = std::make_shared<Character>("Commander Kael", 100, 100);

        // ---- Set up logger ----
        auto logger = std::make_shared<Logger>("output/log.txt");

        // ---- Run the simulation ----
        Simulation sim(world, character, logger);
        sim.run();

        // ---- Build final report summary ----
        std::ostringstream summary;
        summary << "RESULT: " << (sim.didWin() ? "MISSION SUCCESS" : "MISSION FAILED")
                << "\n\n"
                << "Character: " << character->statusSummary()
                << "\n\nInventory:\n";

        for (const auto& item : character->getInventory()) {
            summary << "  - [" << item->typeToString() << "] "
                    << item->getName() << "\n";
        }

        summary << "\nRooms visited:\n";
        for (const auto& pair : world->getAllRooms()) {
            const auto& room = pair.second;
            summary << "  " << (room->isVisited() ? "[X]" : "[ ]")
                    << " " << room->getName() << "\n";
        }

        // ---- Write report ----
        logger->writeReport("output/report.txt", summary.str());

        std::cout << "\n--- FINAL RESULT: "
                  << (sim.didWin() ? "MISSION SUCCESS" : "MISSION FAILED")
                  << " ---\n";

    } catch (const std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
