cmake_minimum_required(VERSION 3.12)
project(Slytherians_Snake_Game)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Slytherians_Snake_Game
        Game.cpp
        Game.h
        Graphics.cpp
        Graphics.h
        main.cpp)
