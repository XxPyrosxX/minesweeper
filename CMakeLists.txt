cmake_minimum_required(VERSION 3.26)
project(minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

include_directories(.)

add_executable(minesweeper
        Button.cpp
        Button.h
        GameState.cpp
        GameState.h
        Minesweeper.cpp
        Minesweeper.h
        Tile.cpp
        Tile.h
        Toolbox.cpp
        Toolbox.h)
target_link_libraries(minesweeper sfml-graphics sfml-audio)
