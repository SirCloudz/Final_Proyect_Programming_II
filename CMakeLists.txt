cmake_minimum_required(VERSION 3.16)
project(Final_Proyect_Programming_II)

set(CMAKE_CXX_STANDARD 20)

add_executable(Final_Proyect_Programming_II
        main.cpp
        src/building.cpp
        src/controller.cpp
        src/game_engine.cpp
        src/map.cpp
        src/renderer.cpp
        src/tile.cpp
        src/unit.cpp
        src/ux.cpp
)
