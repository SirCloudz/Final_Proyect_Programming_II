
#ifndef FINAL_PROYECT_PROGRAMMING_II_TILE_H
#define FINAL_PROYECT_PROGRAMMING_II_TILE_H

#include <string>

enum class Owner
{
    NONE,
    J1,
    J2,
    NEUTRAL
};
enum class UnitType
{
    NONE_U,
    S,
    A,
    C,
    M,
    I
};
enum class BuildingType
{
    NONE_B,
    CU,
    TO,
    GR
};
enum class TerrainType
{
    LL,
    BO,
    MO,
    AG,
    PA
};

class Tile
{
private:
    TerrainType terrain;
    Owner owner;
    UnitType unit;
    Owner unit_owner;
    BuildingType building;
    Owner building_owner;

public:
    Tile();

    // getters / setters
    TerrainType getTerrain() const;
    void setTerrain(TerrainType t);

    Owner getOwner() const;
    void setOwner(Owner o);

    UnitType getUnit() const;
    void setUnit(UnitType u);

    Owner getUnitOwner() const;
    void setUnitOwner(Owner o);

    BuildingType getBuilding() const;
    void setBuilding(BuildingType b);

    Owner getBuildingOwner() const;
    void setBuildingOwner(Owner o);

    void clearUnit();
    void clearBuilding();

    std::string code() const; // e.g. "J1S/LL" or "..../AG"
};


#endif //FINAL_PROYECT_PROGRAMMING_II_TILE_H