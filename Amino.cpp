//
// Created by Dmitry on 19.11.2020.
//

#include "Amino.h"

#include <utility>

Amino::Amino(std::string name) : name(std::move(name)) {}

Amino::Amino(const char *name) : name(name) {}

const std::string &Amino::getName() const {
    return name;
}

void Amino::setName(const std::string &name) {
    Amino::name = name;
}

size_t Amino::hash() const {
    return std::hash<std::string>{}("Amino" + name);
}

bool Amino::operator==(const Amino &other) const {
    return getName() == other.getName();
}

bool Amino::operator!=(const Amino &other) const {
    return !(this->operator==(other));
}

std::string Amino::toString() const {
    return getName();
}

Amino::Amino() {}
