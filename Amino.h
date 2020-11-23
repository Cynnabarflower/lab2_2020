//
// Created by Dmitry on 19.11.2020.
//

#ifndef LAB2_2020_AMINO_H
#define LAB2_2020_AMINO_H


#include <string>

class Amino {
public:
    Amino(std::string name);

    Amino(const char *name);

    Amino();

    const std::string &getName() const;

    void setName(const std::string &name);

    size_t hash() const;


    bool operator==(Amino const &other) const;
    bool operator!=(Amino const &other) const;

    std::string toString() const;

private:
    std::string name;
};


#endif //LAB2_2020_AMINO_H
