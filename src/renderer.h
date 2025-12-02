
#ifndef FINAL_PROYECT_PROGRAMMING_II_RENDERER_H
#define FINAL_PROYECT_PROGRAMMING_II_RENDERER_H

#include "map.h"

class ConsoleRenderer
{
public:
    ConsoleRenderer();
    void render(const Map &map, int turno, int pa, int comida, int metal, int energia);
};

#endif //FINAL_PROYECT_PROGRAMMING_II_RENDERER_H