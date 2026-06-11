//
// Created by zunig on 6/11/2026.
//

#ifndef AVENTURAS_ROOM_H
#define AVENTURAS_ROOM_H


#include <string>
#include <vector>
#include <memory>
#include "Item.h"
#include "Event.h"

// Represents a location (section) aboard the abandoned spaceship
class Room {
public:
    Room(const std::string& id, const std::string& name, const std::string& description);

    std::string getId() const;
    std::string getName() const;
    std::string getDescription() const;

    void addConnection(const std::string& roomId);
    const std::vector<std::string>& getConnections() const;

    void addItem(std::shared_ptr<Item> item);
    std::vector<std::shared_ptr<Item>>& getItems();

    void addEvent(std::shared_ptr<Event> event);
    std::vector<std::shared_ptr<Event>>& getEvents();

    bool isVisited() const;
    void markVisited();

    bool isExit() const;
    void setAsExit(bool value);

    // Overloaded operator for easy console printing
    friend std::ostream& operator<<(std::ostream& os, const Room& room);

private:
    std::string id;
    std::string name;
    std::string description;
    bool visited;
    bool exitRoom;
    std::vector<std::string> connections;           // IDs of adjacent rooms
    std::vector<std::shared_ptr<Item>> items;
    std::vector<std::shared_ptr<Event>> events;
};
#endif //AVENTURAS_ROOM_H
