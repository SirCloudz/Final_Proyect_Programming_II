#include "building.h"

Building::Building(BuildingType t, Owner o) : type(t), owner(o), level(1) {}

std::string Building::to_string() const {
    switch (type)
    {
        case BuildingType::CU:
            return "Cuartel";
        case BuildingType::TO:
            return "Torre";
        case BuildingType::GR:
            return "Granja";
        default:
            return "None";
    }
}