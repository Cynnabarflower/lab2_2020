//
// Created by Dmitry on 19.11.2020.
//

#include "Codon.h"

#include <utility>

Codon::Codon(std::string name) : name(std::move(name)) {}

const std::string &Codon::getName() const {
    return name;
}

void Codon::setName(const std::string &name) {
    Codon::name = name;
}


size_t Codon::hash() const {
    return std::hash<std::string>{}("Codon" + name);
}

bool Codon::operator==(const Codon &other) const {
    return getName() == other.getName();
}

bool Codon::operator!=(const Codon &other) const {
    return !(this->operator==(other));
}

std::string Codon::toString() const {
    return getName();
}

Codon::Codon(const char *name) : name(name) {}

Codon::Codon() {}


