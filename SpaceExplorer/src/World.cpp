//
// Created by zunig on 6/11/2026.
//

#include "World.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

World::World() : startRoomId("") {}

// -----------------------------------------------------------------------
// File format for rooms.txt:
//   ROOM <id> <name (underscores_for_spaces)> <description (underscores)> [EXIT]
//   CONNECT <id1> <id2>
//   START <id>
// -----------------------------------------------------------------------
void World::loadRooms(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open())
        throw std::runtime_error("Cannot open rooms file: " + filepath);

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "ROOM") {
            std::string id, rawName, rawDesc, extra;
            iss >> id >> rawName >> rawDesc;

            // Replace underscores with spaces for readability
            for (char& c : rawName) if (c == '_') c = ' ';
            for (char& c : rawDesc) if (c == '_') c = ' ';

            auto room = std::make_shared<Room>(id, rawName, rawDesc);

            iss >> extra;
            if (extra == "EXIT") room->setAsExit(true);

            rooms[id] = room;

        } else if (token == "CONNECT") {
            std::string id1, id2;
            iss >> id1 >> id2;
            if (rooms.count(id1) && rooms.count(id2)) {
                rooms[id1]->addConnection(id2);
                rooms[id2]->addConnection(id1);
            }

        } else if (token == "START") {
            iss >> startRoomId;
        }
    }

    if (startRoomId.empty())
        throw std::runtime_error("No START room defined in rooms.txt");
}

// -----------------------------------------------------------------------
// File format for items.txt:
//   ITEM <id> <name (underscores)> <type> <value> <roomId>
// -----------------------------------------------------------------------
void World::loadItems(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open())
        throw std::runtime_error("Cannot open items file: " + filepath);

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string token;
        iss >> token;
        if (token != "ITEM") continue;

        std::string id, rawName, typeStr, roomId;
        int value;
        iss >> id >> rawName >> typeStr >> value >> roomId;

        for (char& c : rawName) if (c == '_') c = ' ';

        Item::Type type = parseItemType(typeStr);
        auto item = std::make_shared<Item>(id, rawName, type, value);

        if (rooms.count(roomId)) {
            rooms[roomId]->addItem(item);
        } else {
            throw std::runtime_error("Item references unknown room: " + roomId);
        }
    }
}

// -----------------------------------------------------------------------
// File format for events.txt:
//   ENEMY  <id> <description (underscores)> <damage> <roomId>
//   HAZARD <id> <description (underscores)> <oxygenDrain> <roomId>
//   BONUS  <id> <description (underscores)> <healthGain> <oxygenGain> <roomId>
// -----------------------------------------------------------------------
void World::loadEvents(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open())
        throw std::runtime_error("Cannot open events file: " + filepath);

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string token;
        iss >> token;

        std::shared_ptr<Event> event;
        std::string roomId;

        if (token == "ENEMY") {
            std::string id, rawDesc;
            int damage;
            iss >> id >> rawDesc >> damage >> roomId;
            for (char& c : rawDesc) if (c == '_') c = ' ';
            event = std::make_shared<EnemyEvent>(id, rawDesc, damage);

        } else if (token == "HAZARD") {
            std::string id, rawDesc;
            int drain;
            iss >> id >> rawDesc >> drain >> roomId;
            for (char& c : rawDesc) if (c == '_') c = ' ';
            event = std::make_shared<HazardEvent>(id, rawDesc, drain);

        } else if (token == "BONUS") {
            std::string id, rawDesc;
            int hp, o2;
            iss >> id >> rawDesc >> hp >> o2 >> roomId;
            for (char& c : rawDesc) if (c == '_') c = ' ';
            event = std::make_shared<BonusEvent>(id, rawDesc, hp, o2);

        } else {
            continue;
        }

        if (rooms.count(roomId)) {
            rooms[roomId]->addEvent(event);
        } else {
            throw std::runtime_error("Event references unknown room: " + roomId);
        }
    }
}

std::shared_ptr<Room> World::getRoom(const std::string& id) const {
    auto it = rooms.find(id);
    if (it == rooms.end())
        throw std::runtime_error("Room not found: " + id);
    return it->second;
}

std::shared_ptr<Room> World::getStartRoom() const {
    return getRoom(startRoomId);
}

const std::map<std::string, std::shared_ptr<Room>>& World::getAllRooms() const {
    return rooms;
}

Item::Type World::parseItemType(const std::string& typeStr) const {
    if (typeStr == "OXYGEN")   return Item::Type::OXYGEN;
    if (typeStr == "KEY")      return Item::Type::KEY;
    if (typeStr == "WEAPON")   return Item::Type::WEAPON;
    if (typeStr == "MEDKIT")   return Item::Type::MEDKIT;
    if (typeStr == "ARTIFACT") return Item::Type::ARTIFACT;
    throw std::runtime_error("Unknown item type: " + typeStr);
}
