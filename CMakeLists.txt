cmake_minimum_required(VERSION 3.26)
project(minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

include_directories(.)

add_executable(minesweeper
        src/Button.cpp
        src/Button.h
        src/GameState.cpp
        src/GameState.h
        src/Minesweeper.cpp
        src/Minesweeper.h
        src/Tile.cpp
        src/Tile.h
        src/Toolbox.cpp
        src/Toolbox.h)
target_link_libraries(minesweeper sfml-graphics sfml-audio)
