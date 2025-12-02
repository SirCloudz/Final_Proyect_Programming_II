//
// Created by bl4z3 on 12/2/2025.
//

#ifndef FINAL_PROYECT_PROGRAMMING_II_BUILDING_H
#define FINAL_PROYECT_PROGRAMMING_II_BUILDING_H

#include "tile.h"
#include <string>

struct Building
{
    BuildingType type;
    Owner owner;
    int level;
    Building(BuildingType t = BuildingType::NONE_B, Owner o = Owner::NONE);
    std::string to_string() const;
};

#endif //FINAL_PROYECT_PROGRAMMING_II_BUILDING_H