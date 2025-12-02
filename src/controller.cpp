
#include "controller.h"
#include <sstream>
#include <iostream>

Controller::Controller(GameEngine &engine) : eng(engine) {}

void Controller::loop()
{
    std::string line;
    while (true)
    {
        eng.render(); // show UI
        std::getline(std::cin, line);
        if (!std::cin)
            break;
        if (line.empty())
            continue;
        process_line(line);
        if (eng.quit_requested())
            break;
    }
}

void Controller::process_line(const std::string &line)
{
    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;
    if (cmd == "q" || cmd == "quit")
    {
        eng.request_quit();
        return;
    }
    if (cmd == "e" || cmd == "end")
    {
        eng.end_turn();
        return;
    }
    if (cmd == "m")
    {
        int r, c, nr, nc;
        if (!(iss >> r >> c >> nr >> nc))
        {
            std::cout << "Formato: m r c nr nc\nPress Enter...\n";
            std::string tmp;
            std::getline(std::cin, tmp);
            return;
        }
        eng.player_move(r, c, nr, nc);
        return;
    }
    if (cmd == "r")
    { // reclutar: r r c (tipo por defecto soldado)
        int r, c;
        if (!(iss >> r >> c))
        {
            std::cout << "Formato: r r c\nPress Enter...\n";
            std::string tmp;
            std::getline(std::cin, tmp);
            return;
        }
        eng.recruit(r, c, UnitType::S);
        return;
    }
    if (cmd == "b")
    { // construir: b r c type (Cu/To/Gr)
        int r, c;
        std::string t;
        if (!(iss >> r >> c >> t))
        {
            std::cout << "Formato: b r c type (Cu/To/Gr)\nPress Enter...\n";
            std::string tmp;
            std::getline(std::cin, tmp);
            return;
        }
        BuildingType bt = BuildingType::CU;
        if (t == "To")
            bt = BuildingType::TO;
        else if (t == "Gr")
            bt = BuildingType::GR;
        else
            bt = BuildingType::CU;
        eng.build(r, c, bt);
        return;
    }

    std::cout << "Comando no reconocido.\nPress Enter...";
    std::string tmp;
    std::getline(std::cin, tmp);
}