//
// Created by zunig on 6/11/2026.
//

#include "Room.h"

#include <ostream>

Room::Room(const std::string& id, const std::string& name, const std::string& description)
    : id(id), name(name), description(description), visited(false), exitRoom(false) {}

std::string Room::getId() const { return id; }
std::string Room::getName() const { return name; }
std::string Room::getDescription() const { return description; }

void Room::addConnection(const std::string& roomId) {
    connections.push_back(roomId);
}

const std::vector<std::string>& Room::getConnections() const {
    return connections;
}

void Room::addItem(std::shared_ptr<Item> item) {
    items.push_back(item);
}

std::vector<std::shared_ptr<Item>>& Room::getItems() {
    return items;
}

void Room::addEvent(std::shared_ptr<Event> event) {
    events.push_back(event);
}

std::vector<std::shared_ptr<Event>>& Room::getEvents() {
    return events;
}

bool Room::isVisited() const { return visited; }
void Room::markVisited() { visited = true; }

bool Room::isExit() const { return exitRoom; }
void Room::setAsExit(bool value) { exitRoom = value; }

std::ostream& operator<<(std::ostream& os, const Room& room) {
    os << "[" << room.id << "] " << room.name;
    if (room.exitRoom) os << " (EXIT)";
    return os;
}