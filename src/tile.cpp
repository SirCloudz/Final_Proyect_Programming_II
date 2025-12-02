#include "tile.h"

Tile::Tile()
    : terrain(TerrainType::LL),
      owner(Owner::NONE),
      unit(UnitType::NONE_U),
      unit_owner(Owner::NONE),
      building(BuildingType::NONE_B),
      building_owner(Owner::NONE) {}

TerrainType Tile::getTerrain() const { return terrain; }
void Tile::setTerrain(TerrainType t) { terrain = t; }

Owner Tile::getOwner() const { return owner; }
void Tile::setOwner(Owner o) { owner = o; }

UnitType Tile::getUnit() const { return unit; }
void Tile::setUnit(UnitType u) { unit = u; }

Owner Tile::getUnitOwner() const { return unit_owner; }
void Tile::setUnitOwner(Owner o) { unit_owner = o; }

BuildingType Tile::getBuilding() const { return building; }
void Tile::setBuilding(BuildingType b) { building = b; }

Owner Tile::getBuildingOwner() const { return building_owner; }
void Tile::setBuildingOwner(Owner o) { building_owner = o; }

void Tile::clearUnit()
{
    unit = UnitType::NONE_U;
    unit_owner = Owner::NONE;
}
void Tile::clearBuilding()
{
    building = BuildingType::NONE_B;
    building_owner = Owner::NONE;
}

std::string Tile::code() const
{
    auto terr = [](TerrainType t)
    {
        switch (t)
        {
        case TerrainType::LL:
            return "LL";
        case TerrainType::BO:
            return "BO";
        case TerrainType::MO:
            return "MO";
        case TerrainType::AG:
            return "AG";
        case TerrainType::PA:
            return "PA";
        }
        return "??";
    }(terrain);

    auto pref = [](Owner o)
    {
        switch (o)
        {
        case Owner::J1:
            return "J1";
        case Owner::J2:
            return "J2";
        case Owner::NEUTRAL:
            return "Ne";
        default:
            return "..";
        }
    };

    if (unit != UnitType::NONE_U)
    {
        char tchar = '.';
        switch (unit)
        {
        case UnitType::S:
            tchar = 'S';
            break;
        case UnitType::A:
            tchar = 'A';
            break;
        case UnitType::C:
            tchar = 'C';
            break;
        case UnitType::M:
            tchar = 'M';
            break;
        case UnitType::I:
            tchar = 'I';
            break;
        default:
            tchar = '?';
        }
        return pref(unit_owner) + std::string(1, tchar) + "/" + terr;
    }
    else if (building != BuildingType::NONE_B)
    {
        std::string b;
        switch (building)
        {
        case BuildingType::CU:
            b = "Cu";
            break;
        case BuildingType::TO:
            b = "To";
            break;
        case BuildingType::GR:
            b = "Gr";
            break;
        default:
            b = "??";
            break;
        }
        return pref(building_owner) + b + "/" + terr;
    }
    else
    {
        return ".." + std::string("/") + terr;
    }
}