
#include "renderer.h"
#include <iostream>
#include <iomanip>

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