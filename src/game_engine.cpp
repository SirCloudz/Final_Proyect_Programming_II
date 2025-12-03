#include "game_engine.h"
#include <iostream>

GameEngine::GameEngine()
    : map(12, 12),
      renderer(),
      turno(1),
      pa(MAX_PA),
      comida(START_COMIDA),
      metal(START_METAL),
      energia(START_ENERGIA),
      quit_flag(false)
{
    // initial placement sample (Estado 0)
    map.at(1, 1).setUnit(UnitType::S);
    map.at(1, 1).setUnitOwner(Owner::J1);

    map.at(0, 2).setUnit(UnitType::S);
    map.at(0, 2).setUnitOwner(Owner::J2);

    map.at(3, 2).setBuilding(BuildingType::CU);
    map.at(3, 2).setBuildingOwner(Owner::NEUTRAL);
    map.at(3, 2).setTerrain(TerrainType::MO);

    map.set_terrain_row(5, TerrainType::AG);
}

void GameEngine::render()
{
    renderer.render(map, turno, pa, comida, metal, energia);
}

void GameEngine::player_move(int r, int c, int nr, int nc)
{
    if (pa <= 0)
    {
        std::cout << "Sin PA. Fin de turno requerido. Pres Enter...";
        std::string tmp;
        std::getline(std::cin, tmp);
        return;
    }
    if (!map.in_bounds(r, c) || !map.in_bounds(nr, nc))
    {
        std::cout << "Fuera de rango.\n";
        std::string tmp;
        std::getline(std::cin, tmp);
        return;
    }
    if (!can_move_unit(r, c, nr, nc))
    {
        std::cout << "Movimiento invalido.\n";
        std::string tmp;
        std::getline(std::cin, tmp);
        return;
    }
    Tile &src = map.at(r, c);
    Tile &dst = map.at(nr, nc);
    if (dst.getUnit() != UnitType::NONE_U)
    {
        // combat
        resolve_combat(r, c, nr, nc);
    }
    else
    {
        // move
        dst.setUnit(src.getUnit());
        dst.setUnitOwner(src.getUnitOwner());
        src.clearUnit();
    }
    pa -= 1;
}

bool GameEngine::can_move_unit(int r, int c, int nr, int nc)
{
    if (!((r == nr && std::abs(c - nc) == 1) || (c == nc && std::abs(r - nr) == 1)))
        return false; // only orthogonal
    Tile &src = map.at(r, c);
    if (src.getUnit() == UnitType::NONE_U)
        return false;
    // water check: no naval units implemented
    if (map.at(nr, nc).getTerrain() == TerrainType::AG)
        return false;
    return true;
}

void GameEngine::resolve_combat(int r, int c, int nr, int nc)
{
    Tile &src = map.at(r, c);
    Tile &dst = map.at(nr, nc);
    if (src.getUnitOwner() == dst.getUnitOwner())
    {
        std::cout << "Destino ocupado por aliado.\n";
        std::string tmp;
        std::getline(std::cin, tmp);
        return;
    }
    // simple combat: attacker wins (could expand)
    dst.setUnit(src.getUnit());
    dst.setUnitOwner(src.getUnitOwner());
    src.clearUnit();
    // if building present and enemy owned, capture
    if (dst.getBuilding() != BuildingType::NONE_B)
    {
        dst.setBuildingOwner(dst.getUnitOwner());
    }
}

void GameEngine::recruit(int r, int c, UnitType ut)
{
    if (pa <= 0)
    {
        std::cout << "Sin PA.\n";
        std::string tmp;
        std::getline(std::cin, tmp);
        return;
    }
    if (!map.in_bounds(r, c))
    {
        std::cout << "Fuera de rango.\n";
        std::string tmp;
        std::getline(std::cin, tmp);
        return;
    }
    Tile &t = map.at(r, c);
    if (t.getUnit() != UnitType::NONE_U)
    {
        std::cout << "Casilla ocupada.\n";
        std::string tmp;
        std::getline(std::cin, tmp);
        return;
    }
    // only allow if there's a J1 Cuartel or owned tile (simple rule)
    bool allowed = false;
    if (t.getOwner() == Owner::J1)
        allowed = true;
    // allow recruit at J1Cu if present
    if (t.getBuilding() == BuildingType::CU && t.getBuildingOwner() != Owner::NONE)
    {
        if (t.getBuildingOwner() == Owner::J1)
            allowed = true;
    }
    if (!allowed)
    {
        std::cout << "No puedes reclutar aqui.\n";
        std::string tmp;
        std::getline(std::cin, tmp);
        return;
    }

    // cost: 1 comida,1 metal
    if (comida < 1 || metal < 1)
    {
        std::cout << "Recursos insuficientes.\n";
        std::string tmp;
        std::getline(std::cin, tmp);
        return;
    }
    comida -= 1;
    metal -= 1;
    t.setUnit(ut);
    t.setUnitOwner(Owner::J1);
    pa -= 1;
}

void GameEngine::build(int r, int c, BuildingType bt)
{
    if (pa <= 0)
    {
        std::cout << "Sin PA.\n";
        std::string tmp;
        std::getline(std::cin, tmp);
        return;
    }
    if (!map.in_bounds(r, c))
    {
        std::cout << "Fuera de rango.\n";
        std::string tmp;
        std::getline(std::cin, tmp);
        return;
    }
    Tile &t = map.at(r, c);
    if (t.getUnit() != UnitType::NONE_U)
    {
        std::cout << "Desocupa la casilla antes de construir.\n";
        std::string tmp;
        std::getline(std::cin, tmp);
        return;
    }
    if (t.getBuilding() != BuildingType::NONE_B)
    {
        std::cout << "Ya existe edificio.\n";
        std::string tmp;
        std::getline(std::cin, tmp);
        return;
    }
    // can build only on owned by J1
    if (t.getOwner() != Owner::J1)
    {
        std::cout << "No controlas esta casilla.\n";
        std::string tmp;
        std::getline(std::cin, tmp);
        return;
    }

    // cost simplified
    int cost_metal = 1;
    int cost_energy = 1;
    if (bt == BuildingType::TO)
    {
        cost_metal = 2;
        cost_energy = 1;
    }
    if (metal < cost_metal || energia < cost_energy)
    {
        std::cout << "Recursos insuficientes.\n";
        std::string tmp;
        std::getline(std::cin, tmp);
        return;
    }

    metal -= cost_metal;
    energia -= cost_energy;
    t.setBuilding(bt);
    t.setBuildingOwner(Owner::J1);
    pa -= 1;
}

void GameEngine::end_turn()
{
    // world phase: simple guardian move (move J2 units down-right if possible)
    world_phase();
    // production & maintenance
    // production: each J1Gr (granjas) produce +2 comida
    for (int r = 0; r < map.num_rows(); ++r)
    {
        for (int c = 0; c < map.num_cols(); ++c)
        {
            const Tile &t = map.at(r, c);
            if (t.getBuilding() == BuildingType::GR && t.getBuildingOwner() == Owner::J1)
            {
                comida += 2;
            }
            if (t.getBuilding() == BuildingType::CU && t.getBuildingOwner() == Owner::NEUTRAL)
            {
                // neutral cuartel does nothing unless captured
            }
        }
    }
    // maintenance: each unit costs 1 comida
    int units = 0;
    for (int r = 0; r < map.num_rows(); ++r)
        for (int c = 0; c < map.num_cols(); ++c)
            if (map.at(r, c).getUnit() != UnitType::NONE_U)
                units++;
    int consume = units;
    if (comida >= consume)
        comida -= consume;
    else
    {
        int shortage = consume - comida;
        comida = 0;
        for (int r = map.num_rows() - 1; r >= 0 && shortage > 0; --r)
        {
            for (int c = map.num_cols() - 1; c >= 0 && shortage > 0; --c)
            {
                if (map.at(r, c).getUnit() != UnitType::NONE_U)
                {
                    map.at(r, c).clearUnit();
                    shortage--;
                }
            }
        }
    }
    turno++;
    pa = MAX_PA;
}

void GameEngine::world_phase()
{
    for (int r = 0; r < map.num_rows(); ++r)
    {
        for (int c = map.num_cols() - 1; c >= 0; --c)
        {
            Tile &t = map.at(r, c);
            if (t.getUnitOwner() == Owner::J2)
            {
                int nr = r;
                int nc = c + 1;
                if (map.in_bounds(nr, nc) && map.at(nr, nc).getUnit() == UnitType::NONE_U && map.at(nr, nc).getTerrain() != TerrainType::AG)
                {
                    map.at(nr, nc).setUnit(t.getUnit());
                    map.at(nr, nc).setUnitOwner(Owner::J2);
                    t.clearUnit();
                }
            }
        }
    }
}

void GameEngine::request_quit() { quit_flag = true; }
bool GameEngine::quit_requested() const { return quit_flag; }
