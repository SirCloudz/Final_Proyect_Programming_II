#include "map.h"
#include <iostream>
#include <iomanip>


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





Map::Map(int r, int c) : rows(r), cols(c), data(r, std::vector<Tile>(c)) {}

bool Map::in_bounds(int r, int c) const
{
    return r >= 0 && c >= 0 && r < rows && c < cols;
}

Tile &Map::at(int r, int c) { return data[r][c]; }
const Tile &Map::at(int r, int c) const { return data[r][c]; }
const std::vector<std::vector<Tile>> &Map::grid() const { return data; }
int Map::num_rows() const { return rows; }
int Map::num_cols() const { return cols; }

void Map::set_terrain_row(int row, TerrainType t)
{
    if (row < 0 || row >= rows)
        return;
    for (int c = 0; c < cols; ++c)
        data[row][c].setTerrain(t);
}

void Map::clear()
{
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            data[r][c] = Tile();
}


ConsoleRenderer::ConsoleRenderer() {}

void ConsoleRenderer::render(const Map &map, int turno, int pa, int comida, int metal, int energia)
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    std::cout << "\x1B[2J\x1B[H";
#endif

    std::cout << "Turno #" << turno << "    PA=" << pa << "    Recursos: Comida=" << comida
              << " Metal=" << metal << " Energia=" << energia << "\n";
    std::cout << "------------------------------------------------------------\n";

    const auto &g = map.grid();
    int rows = map.num_rows();
    int cols = map.num_cols();

    std::cout << "    ";
    for (int c = 0; c < cols; ++c)
        std::cout << std::setw(6) << c;
    std::cout << "\n";

    for (int r = 0; r < rows; ++r)
    {
        std::cout << std::setw(3) << r;
        for (int c = 0; c < cols; ++c)
        {
            std::cout << std::setw(6) << g[r][c].code();
        }
        std::cout << "\n";
    }
    std::cout << "------------------------------------------------------------\n";
    std::cout << "Comandos: m r c nr nc  | r r c (reclutar) | b r c type (construir) | e (end turn) | q (quit)\n";
    std::cout << "Ejemplo mover: m 1 1 1 2\n";
}

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
