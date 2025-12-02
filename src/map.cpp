#include "map.h"

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