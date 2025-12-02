
#ifndef FINAL_PROYECT_PROGRAMMING_II_MAP_H
#define FINAL_PROYECT_PROGRAMMING_II_MAP_H

#include <vector>
#include "tile.h"

class Map
{
private:
    int rows;
    int cols;
    std::vector<std::vector<Tile>> data;

public:
    Map(int r = 12, int c = 12);

    bool in_bounds(int r, int c) const;
    Tile &at(int r, int c);
    const Tile &at(int r, int c) const;
    const std::vector<std::vector<Tile>> &grid() const;
    int num_rows() const;
    int num_cols() const;

    void set_terrain_row(int row, TerrainType t);
    void clear();
};

#endif //FINAL_PROYECT_PROGRAMMING_II_MAP_H