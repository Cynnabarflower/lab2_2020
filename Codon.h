//
// Created by Dmitry on 19.11.2020.
//

#ifndef LAB2_2020_CODON_H
#define LAB2_2020_CODON_H


#include <string>

class Codon {
public:
    Codon(std::string name);

    Codon(const char *name);

    Codon();

    const std::string &getName() const;

    void setName(const std::string &name);

    bool operator==(Codon const &other) const;
    bool operator!=(Codon const &other) const;

    std::string toString() const;
    size_t hash() const;

private:
    std::string name;
};


#endif //LAB2_2020_CODON_H
