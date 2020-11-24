cmake_minimum_required(VERSION 3.15)
project(Pacman)

set(CMAKE_CXX_STANDARD 14)


if(APPLE)
    link_directories(/usr/local/opt/libomp/lib)
    include_directories(/usr/local/opt/libomp/include)

    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)

    if(CMAKE_C_COMPILER_ID MATCHES "Clang\$")
        set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp")
        set(OpenMP_C_LIB_NAMES "omp")
        set(OpenMP_omp_LIBRARY omp)
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang\$")
        set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp")
        set(OpenMP_CXX_LIB_NAMES "omp")
        set(OpenMP_omp_LIBRARY omp)
    endif()

endif()

find_package(OpenMP REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework GLUT -framework OpenGL -Wno-deprecated")
add_executable(Pacman Config.h Utils.h Utils.cpp Game.h Game.cpp Map.h Map.cpp Maze.h Maze.cpp Objects.h Objects.cpp main.cpp PathFinder.cpp PathFinder.h)
target_link_libraries(Pacman PRIVATE OpenMP::OpenMP_CXX)
