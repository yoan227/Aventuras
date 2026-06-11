//
// Created by zunig on 6/11/2026.
//


#ifndef ITEM_H
#define ITEM_H

#include <string>

// Represents an interactive object found in a room
class Item {
public:
    enum class Type { OXYGEN, KEY, WEAPON, MEDKIT, ARTIFACT };

    Item(const std::string& id, const std::string& name, Type type, int value);

    std::string getId() const;
    std::string getName() const;
    Type getType() const;
    int getValue() const;

    std::string typeToString() const;

private:
    std::string id;
    std::string name;
    Type type;
    int value; // effect magnitude (oxygen units, health points, etc.)
};

#endif

