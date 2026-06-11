//
// Created by zunig on 6/11/2026.
//

#ifndef AVENTURAS_WORLD_H
#define AVENTURAS_WORLD_H


#include <string>
#include <map>
#include <memory>
#include "Room.h"
#include "Item.h"
#include "Event.h"

// Responsible for loading the adventure world from data files
class World {
public:
    World();

    void loadRooms(const std::string& filepath);
    void loadItems(const std::string& filepath);
    void loadEvents(const std::string& filepath);

    std::shared_ptr<Room> getRoom(const std::string& id) const;
    std::shared_ptr<Room> getStartRoom() const;

    const std::map<std::string, std::shared_ptr<Room>>& getAllRooms() const;

private:
    std::map<std::string, std::shared_ptr<Room>> rooms;
    std::string startRoomId;

    Item::Type parseItemType(const std::string& typeStr) const;
};
#endif //AVENTURAS_WORLD_H
