
#ifndef FINAL_PROYECT_PROGRAMMING_II_UNIT_H
#define FINAL_PROYECT_PROGRAMMING_II_UNIT_H

#include "tile.h"
#include <string>

struct Unit
{
    UnitType type;
    Owner owner;
    int hp;
    int atk;
    int def;
    int move; // movement points (abstract)
    Unit(UnitType t = UnitType::NONE_U, Owner o = Owner::NONE);
    std::string to_string() const;
};

#endif //FINAL_PROYECT_PROGRAMMING_II_UNIT_H