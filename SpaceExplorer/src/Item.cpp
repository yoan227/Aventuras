//
// Created by zunig on 6/11/2026.
//


#include "Item.h"

Item::Item(const std::string& id, const std::string& name, Type type, int value)
    : id(id), name(name), type(type), value(value) {}

std::string Item::getId() const { return id; }
std::string Item::getName() const { return name; }
Item::Type Item::getType() const { return type; }
int Item::getValue() const { return value; }

std::string Item::typeToString() const {
    switch (type) {
        case Type::OXYGEN:   return "OXYGEN";
        case Type::KEY:      return "KEY";
        case Type::WEAPON:   return "WEAPON";
        case Type::MEDKIT:   return "MEDKIT";
        case Type::ARTIFACT: return "ARTIFACT";
        default:             return "UNKNOWN";
    }
}
