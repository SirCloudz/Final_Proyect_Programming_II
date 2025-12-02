

#ifndef FINAL_PROYECT_PROGRAMMING_II_GAME_ENGINE_H
#define FINAL_PROYECT_PROGRAMMING_II_GAME_ENGINE_H

#include "map.h"
#include "renderer.h"
#include "config.h"

class GameEngine
{
public:
    GameEngine();

    // UI
    void render();

    // actions from controller
    void player_move(int r, int c, int nr, int nc);
    void recruit(int r, int c, UnitType ut);
    void build(int r, int c, BuildingType bt);
    void end_turn();

    // control
    void request_quit();
    bool quit_requested() const;

private:
    Map map;
    ConsoleRenderer renderer;

    int turno;
    int pa;
    int comida, metal, energia;
    bool quit_flag;

    // helpers
    void world_phase();
    bool can_move_unit(int r, int c, int nr, int nc);
    void resolve_combat(int r, int c, int nr, int nc);
};


#endif //FINAL_PROYECT_PROGRAMMING_II_GAME_ENGINE_H