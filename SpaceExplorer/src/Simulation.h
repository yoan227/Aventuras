//
// Created by zunig on 6/11/2026.
//

#ifndef AVENTURAS_SIMULATION_H
#define AVENTURAS_SIMULATION_H




#include <memory>
#include "World.h"
#include "Character.h"
#include "Logger.h"

// Drives the main simulation loop
class Simulation {
public:
    Simulation(std::shared_ptr<World> world,
               std::shared_ptr<Character> character,
               std::shared_ptr<Logger> logger);

    void run();
    bool didWin() const;

private:
    std::shared_ptr<World> world;
    std::shared_ptr<Character> character;
    std::shared_ptr<Logger> logger;
    bool won;

    void enterRoom(std::shared_ptr<Room> room);
    void processItems(std::shared_ptr<Room> room);
    void processEvents(std::shared_ptr<Room> room);

    // Returns the next room to move to (BFS-like automatic traversal)
    std::shared_ptr<Room> chooseNextRoom(std::shared_ptr<Room> current);
};



#endif //AVENTURAS_SIMULATION_H
