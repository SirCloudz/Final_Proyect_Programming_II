#include "unit.h"

Unit::Unit(UnitType t, Owner o) : type(t), owner(o)
{
    // stats simple por tipo
    switch (type)
    {
        case UnitType::S:
            hp = 10;
            atk = 4;
            def = 2;
            move = 2;
            break;
        case UnitType::A:
            hp = 8;
            atk = 3;
            def = 1;
            move = 2;
            break;
        case UnitType::C:
            hp = 12;
            atk = 5;
            def = 3;
            move = 2;
            break;
        case UnitType::M:
            hp = 6;
            atk = 5;
            def = 0;
            move = 2;
            break;
        case UnitType::I:
            hp = 7;
            atk = 1;
            def = 1;
            move = 2;
            break;
        default:
            hp = 0;
            atk = 0;
            def = 0;
            move = 0;
            break;
    }
}

std::string Unit::to_string() const
{
    std::string t;
    switch (type)
    {
        case UnitType::S:
            t = "Soldado";
            break;
        case UnitType::A:
            t = "Arquero";
            break;
        case UnitType::C:
            t = "Caballero";
            break;
        case UnitType::M:
            t = "Mago";
            break;
        case UnitType::I:
            t = "Ingeniero";
            break;
        default:
            t = "None";
            break;
    }
    return t;
}