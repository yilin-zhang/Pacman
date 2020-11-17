cmake_minimum_required(VERSION 3.15)
project(Pacman)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework GLUT -framework OpenGL -Wno-deprecated -pthread")

add_executable(Pacman Config.h Utils.h Utils.cpp Maze.h Maze.cpp Objects.h Objects.cpp main.cpp)
